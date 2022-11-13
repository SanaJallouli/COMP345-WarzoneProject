#include "Order.hpp"


Order::Order()
{
    type_id = new int();
    valid = new bool();
    orderName = new string();

}

Order::Order(Player* player)
{
    type_id = new int();
    valid = new bool();
    orderName = new string();
    owner = player;
}


Order::~Order()
{
    delete valid;
    valid = nullptr;

    delete type_id;
    type_id = nullptr;

    for (std::vector<string*>::iterator it = orders.begin(); it != orders.end(); ++it) {
        delete* it;
        *it = nullptr;
    }


}

Order::Order(const Order& O)
{

    orders = vector<string*>(O.orders);
    type_id = new int(*O.type_id);
    valid = new bool(*O.valid);
    orderName = new string(*O.orderName);
}

Order& Order::operator=(const Order& O) {
    orders = vector<string*>(O.orders);
    type_id = new int(*type_id);
    valid = new bool(*O.valid);
    orderName = new string(*O.orderName);
    return *this;
}

ostream& operator<<(ostream& strm, const Order& O) {
    return strm << "Order : " << O.orderName;
}






void Order::set_type_id(int num)
{
    *type_id = num;
}

string* Order::get_type()
{
    return ((orders).at(*type_id));
}



//******************** DEPLOY *******************
Deploy::Deploy()
{
    cout << "deploy is creating..." << endl;
    set_type_id(0);
    orderName = new string("deploy");
}

Deploy::~Deploy()
{
    delete  type;
    type = nullptr;
}
//copy constructor
Deploy::Deploy(Player* p,int t, Territory * Destination): Order(p)
{
    set_type_id(0);
    troops = t;
    Desti = Destination;
}
Deploy::Deploy(const Deploy& d) : Order(d)
{
    type = new string(*(d.type));
}
// assignment operator
Deploy& Deploy::operator=(const Deploy& d) {
    type = new string(*(d.type));
    return *this;
};

// cout operator
ostream& operator<<(ostream& strm, const Deploy& d) {
    return strm << "TYPE : " << d.type;
};

string* Deploy::get_type()
{
    return type;
}

bool  Deploy::validate() {
    if (*owner->armies < troops) {
        cout << "Cannot execute order deploy from player :" << owner->m_name << " as player has less troops" << endl;
        return false;
    }
    bool found = (std::find(owner->territories.begin(), owner->territories.end(), Desti) != owner->territories.end());
        if (!found) {
            cout << "Cannot execute order deploy from player :" << *owner->m_name << " as player does not own territory : " << *Desti->m_name<<endl;
            return false;
    }
        return true;

}

bool  Deploy::execute() {
    if (validate()) {
        *owner->armies = *owner->armies - troops;
        *Desti->armies = *Desti->armies + troops;
        return true;
    }
    return false;
}
//**************ADVANCE *****************
Advance::Advance()
{
    cout << "advance is creating..." << endl;
    set_type_id(1);

}
Advance::Advance(Player* p, Territory* Source, int t, Territory* Destination) : Order(p)
{
    set_type_id(1);

    troops = t;
    Desti = Destination;
    src = Source;
}
Advance::~Advance()
{
    delete  type;
    type = nullptr;
}

string* Advance::get_type()
{
    return type;
}

Advance& Advance::operator=(const Advance& a) {
    Order :: operator = (a);
    type = new string(*(a.type));
    return *this;
};


Advance::Advance(const Advance& d) : Order(d)
{
    type = new string(*(d.type));
}
// cout operator
ostream& operator<<(ostream& strm, const Advance& a) {
    return strm << "TYPE : " << a.type;
}


 bool Advance::validate() {
     bool found = (std::find(owner->territories.begin(), owner->territories.end(), src) != owner->territories.end());
     if (!found) {
         cout << "Cannot execute order Advance from player :" << *owner->m_name << " as player does not own territory : " << *src->m_name << endl;
         return false;
     }
     if (!src->isAdjacent(Desti)) {
         cout << "Cannot execute order Advance from player :" << *owner->m_name << " as territory : " << *src->m_name <<" and Territory "<<*Desti->m_name<<" are not adjacent"<< endl;
         return false;
     }
     if (troops>*src->armies) {
         cout << "Cannot execute order Advance from player :" << *owner->m_name << " as territory : " << *src->m_name << " have less armies than indicated "<< endl;
         return false;
     }
     return true;
}

 bool Advance::execute() {

     if (!validate()) {
         return false;
     }

     bool found = (std::find(owner->territories.begin(), owner->territories.end(), Desti) != owner->territories.end());
     if (found) {
         *src->armies = *src->armies - troops;
         *Desti->armies = *Desti->armies + troops;
         return true;
     }
     *src->armies = *src->armies - troops;
     while (troops > 0 && Desti->armies > 0)
     {
         srand(time(NULL));
         if (rand() % 10 < 6)
             *Desti->armies= *Desti->armies-1;
          if (rand() % 10 < 7)
              troops--;
     }
     if (troops == 0) {
         cout << "Player " << *owner->m_name << " could not conquer Territory :" << *Desti->m_name << "and left " << *Desti->armies << " units" << endl;
         return true;
     }
     else {
         /// NEEED TO CHANGE OWNERSHIP !!!!!!!! REMOVE FROM PLAYER OTHER LIST 
         cout << "Player " << *owner->m_name << "  conquered Territory :" << *Desti->m_name << "and left " << *Desti->armies << " units" << endl;
         *Desti->armies = troops;
         owner->recieve_card = true;
     }
        

 
     return true;


 }



//***************BOMB ******************
Bomb::Bomb()
{
    cout << "bomb is creating..." << endl;
    set_type_id(2);

}
Bomb::Bomb(Player* p,  Territory* Destination) : Order(p)
{
    set_type_id(2);

    Desti = Destination;

}

Bomb::~Bomb()
{
    delete  type;
    type = nullptr;
}

string* Bomb::get_type()
{
    return type;
}


Bomb& Bomb::operator=(const Bomb& B) {
    Order :: operator = (B);
    type = new string(*(B.type));
    return *this;
};

Bomb::Bomb(const Bomb& d) : Order(d)
{
    type = new string(*(d.type));
}

// cout operator
ostream& operator<<(ostream& strm, const Bomb& a) {

    return strm << "TYPE : " << a.type;
}

 bool Bomb::validate() {
     bool found = (std::find(owner->territories.begin(), owner->territories.end(), Desti) != owner->territories.end());
     if (!found) {
         cout << "Cannot execute order Bomb  from player :" << *owner->m_name << " as player own territory : " << *Desti->m_name << endl;
         return false;
     }
     std::list<Territory*>::iterator itCont;
     bool isadjacent=false;
     for (itCont = owner->territories.begin(); itCont != owner->territories.end(); ++itCont) {
         if (Desti->isAdjacent(*itCont)) {
             isadjacent = true;

         }
     }
     if (isadjacent == false) {
         cout << "Cannot execute order Bomb  from player :" << *owner->m_name << " as player does not own territory that is adjacent to : " << *Desti->m_name << endl;
         return false;
     }

     return true;
}

 bool Bomb::execute() {
     if (!validate())
         return false;
     *Desti->armies = *Desti->armies / 2;
     return true;
}

//*************BLOCKADE *******************
Blockade::Blockade()
{
    cout << "blockade is creating..." << endl;
    set_type_id(3);

}
Blockade::Blockade(Player* p, Territory* Destination) : Order(p)
{
    set_type_id(3);

    Desti = Destination;

}

Blockade::~Blockade()
{
    delete  type;
    type = nullptr;
}
string* Blockade::get_type()
{
    return type;
}

Blockade& Blockade::operator=(const Blockade& B) {
    Order :: operator = (B);
    type = new string(*(B.type));
    return *this;
};

Blockade::Blockade(const Blockade& d) : Order(d)
{
    type = new string(*(d.type));
}


// cout operator
ostream& operator<<(ostream& strm, const Blockade& a) {

    return strm << "TYPE : " << a.type;
}
 bool Blockade::validate() {
     bool found = (std::find(owner->territories.begin(), owner->territories.end(), Desti) != owner->territories.end());
     if (!found) {
         cout << "Cannot execute order Advance from player :" << *owner->m_name << " as player does not own territory : " << *Desti->m_name << endl;
         return false;
     }
     return true;
}

 bool Blockade::execute() {
     if (!validate()) {
         return false;
     }
     /// <summary>
     /// REMOVE OWNERSHIP FOR THIS TERRITORY  
     /// and create neutral player and add it to the list of player 
     /// </summary>
     /// <returns></returns>
     
     *Desti->armies = *Desti->armies * 2;
     return true;
}

//**********airlift
Airlift::Airlift()
{
    cout << "airlift is creating..." << endl;
    set_type_id(4);

}
Airlift::Airlift(Player* p, Territory* Source, int t, Territory* Destination) : Order(p)
{
    set_type_id(4);

    troops = t;
    Desti = Destination;
    src = Source;
}
Airlift::~Airlift()
{
    delete  type;
    type = nullptr;
}
string* Airlift::get_type()
{
    return type;
}

Airlift& Airlift::operator=(const Airlift& a) {
    Order :: operator = (a);
    type = new string(*(a.type));
    return *this;
};


Airlift::Airlift(const Airlift& d) : Order(d)
{
    type = new string(*(d.type));
}
// cout operator
ostream& operator<<(ostream& strm, const Airlift& a) {

    return strm << "TYPE : " << a.type;
}

 bool Airlift::validate() {
     bool found = (std::find(owner->territories.begin(), owner->territories.end(), Desti) != owner->territories.end());
     if (!found) {
         cout << "Cannot execute order Airlift from player :" << *owner->m_name << " as player does not own territory : " << *Desti->m_name << endl;
         return false;
     }
      found = (std::find(owner->territories.begin(), owner->territories.end(), src) != owner->territories.end());
     if (!found) {
         cout << "Cannot execute order Airlift from player :" << *owner->m_name << " as player does not own territory : " << *src->m_name << endl;
         return false;
     }
     return true;
}

 bool Airlift::execute() {
     if (!validate()) {
         return false;
     }
     *src->armies = *src->armies - troops;
     *Desti->armies = *Desti->armies + troops;
     return true;
}


//************NEGOTIATE *************

Negotiate::Negotiate()
{
    cout << "negotiate is creating..." << endl;
    set_type_id(5);

}
Negotiate::Negotiate(Player* p, Player* negotiated) : Order(p)
{
   
    set_type_id(5);

    Negotiated = negotiated;
}
Negotiate::~Negotiate()
{
    delete  type;
    type = nullptr;
}
string* Negotiate::get_type()
{
    return type;
}


// assignment operator
Negotiate& Negotiate::operator=(const Negotiate& a) {
    Order :: operator = (a);
    type = new string(*(a.type));
    return *this;
};



// cout operator
ostream& operator<<(ostream& strm, const Negotiate& a) {
    return strm << "TYPE : " << a.type;
}


Negotiate::Negotiate(const Negotiate& d) : Order(d)
{
    type = new string(*(d.type));
}

 bool Negotiate::validate() {
     if (*owner->m_name != *Negotiated->m_name) {

         cout << "Cannot execute order Negotiate from player :" << *owner->m_name << " as player cannot negociate with himself "<< endl;
      
         return false;
     }
     std::list<Territory*>::iterator itCont;
     bool isadjacent = false;
     for (itCont = Negotiated->Territory_to_attackg.begin(); itCont != Negotiated->Territory_to_attackg.end(); ++itCont) {
         if (*owner->m_name== *(*itCont)->player_owner) {
       cout << "Cannot execute order Negotiate from player :" << *owner->m_name << " as player :  "<< *Negotiated ->m_name<<"is attacking him" << endl;
       return false;
         }
     }

     return true;
}

 bool Negotiate::execute() {
     if (!validate()) {
         return false;
     }

     Negotiated->CannotAttack.insert(Negotiated->CannotAttack.begin(), owner);
     owner->CannotAttack.insert(owner->CannotAttack.begin(), Negotiated);

     return true;
}

//*************order list*********************

void OrdersList::set_order_list(Order* an_order)
{
    vec_order_list.push_back(an_order);
}

OrdersList::OrdersList()
{
    vec_order_list = vector<Order*>();
};


OrdersList::~OrdersList()
{

};

vector<Order*> OrdersList::get_order_list()
{
    return vec_order_list;
}

void OrdersList::remove(Order* oneOrder)
{
    for (int i = 0; i < vec_order_list.size(); i++) {
        if (*(oneOrder->get_type()) == *(vec_order_list.at(i)->get_type())) {
            cout << "deleting the order : " << *(oneOrder->get_type()) << endl;
            vec_order_list.erase(vec_order_list.begin() + i);
            return;
        }
    }
}

void OrdersList::move(int position, int new_position)
{
    if (position >= 0 && position < vec_order_list.size() && new_position >= 0 && new_position < vec_order_list.size())
    {
        vec_order_list.insert(vec_order_list.begin() + new_position, vec_order_list.at(position));
        vec_order_list.erase(vec_order_list.begin() + position);
        cout << "moved succeessfully" << endl;
    }
    else if (new_position == vec_order_list.size())
    {
        vec_order_list.push_back(vec_order_list.at(position));
        vec_order_list.erase(vec_order_list.begin() + position);
        cout << "moved succeessfully" << endl;
    }
    else {
        cout << "not valid position" << endl;
    }
}

// assignment operator
OrdersList& OrdersList::operator=(const OrdersList& o) {
    vec_order_list = vector<Order*>(o.vec_order_list);
    return *this;
};


// cout operator
ostream& operator<<(ostream& strm, const OrdersList& a) {
    return  strm << "Orders stream insertion operator" << endl;
}



// copy constructor
OrdersList::OrdersList(const OrdersList& d)
{
    vec_order_list = vector<Order*>(d.vec_order_list);
}