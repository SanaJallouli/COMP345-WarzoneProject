#include "Order.hpp"


Order::Order()
{
    type_id = new int();
    valid = new bool();
    orderName = new string();

}

Order::Order(Player* player, Command* c, LogObserver* l)
{
    type_id = new int();
    valid = new bool();
    orderName = new string();
    currentCommand = c;
    owner = player;
    lo = l;
    Attach(lo);
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

string Order::stringToLog()
{
    return logging;
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
Deploy::Deploy(Player* p,int t, Territory * Destination,Command* c , LogObserver* l ): Order(p,c,l)
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
        currentCommand->setEffect("Cannot execute order deploy from player :" + *owner->m_name + " as player has less troops");
    
        cout << "Cannot execute order deploy from player :" << *owner->m_name << " as player has less troops" << endl;
        return false;
    }
    bool found = (std::find(owner->territories.begin(), owner->territories.end(), Desti) != owner->territories.end());
        if (!found) {
            currentCommand->setEffect("Cannot execute order deploy from player :" + *owner->m_name + " as player does not own territory : " + *Desti->m_name);

            cout << "Cannot execute order deploy from player :" << *owner->m_name << " as player does not own territory : " << *Desti->m_name<<endl;
            return false;
    }
        return true;

}

bool  Deploy::execute() {
    if (validate()) {
        *owner->armies = *owner->armies - troops;
        *Desti->armies = *Desti->armies + troops;
        logging = "executing the order deploy ";
        Notify(this);
        currentCommand->setEffect("Player " + *owner->m_name + " deployed :" + std::to_string(troops) + "  To " + *Desti->m_name);
        cout << "Player " << *owner->m_name << " deployed :" << troops << "  To " << *Desti->m_name  << endl;
 
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
Advance::Advance(Player* p, Territory* Source, int t, Territory* Destination,Command* c ,LogObserver* l ): Order(p,c,l)
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
         currentCommand->setEffect("Cannot execute order Advance from player :" + *owner->m_name + " as player does not own territory : " + *src->m_name  );

         cout << "Cannot execute order Advance from player :" << *owner->m_name << " as player does not own territory : " << *src->m_name << endl;
         return false;
     }
     Player* attacked = owner->getplayer(owner->AllPlayers, *Desti->player_owner);
      found = (std::find(owner->CannotAttack.begin(), owner->CannotAttack.end(), attacked) != owner->CannotAttack.end());

     if (found) {
         currentCommand->setEffect("Cannot execute order Advance from player :" + *owner->m_name + " as player is nogociating with him : " + *src->m_name);

         cout << "Cannot execute order Advance from player :" + *owner->m_name + " as player is nogociating with him : " + *src->m_name << endl;
         return false;
     }

     if (!src->isAdjacent(Desti)) {
         currentCommand->setEffect("Cannot execute order Advance from player :" + *owner->m_name + " as territory : " + *src->m_name + " and Territory " + *Desti->m_name + " are not adjacent");

         cout << "Cannot execute order Advance from player :" << *owner->m_name << " as territory : " << *src->m_name <<" and Territory "<<*Desti->m_name<<" are not adjacent"<< endl;
         return false;
     }
     if (troops>*src->armies) {
         currentCommand->setEffect("Cannot execute order Advance from player :" + *owner->m_name + " as territory : " + *src->m_name + " have less armies than indicated ");

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
     
         if (getTerritory(owner->territories,*Desti->m_name) != nullptr) {
             owner->Territory_to_defend.insert(owner->Territory_to_defend.begin(), Desti);

         }else 
             owner->Territory_to_attack.insert(owner->Territory_to_attack.begin(), Desti);


         *src->armies = *src->armies - troops;
         *Desti->armies = *Desti->armies + troops;
         logging = "exectuting the order Advance for player  " + *owner->m_name;
         Notify(this);
         currentCommand->setEffect("Player " + *owner->m_name + "  advanced to Territory : " + *Desti->m_name + " and moved  " + std::to_string(*Desti->armies) + " units");
         cout << "Player " + *owner->m_name + "  advanced to Territory : " + *Desti->m_name + " and moved  " + std::to_string(*Desti->armies) + " units";
         return true;
     }
     *src->armies = *src->armies - troops;
     while (troops > 0 && *Desti->armies > 0)
     {
         srand(time(NULL));
         if (rand() % 10 < 6)
             *Desti->armies= *Desti->armies-1;
          if (rand() % 10 < 7)
              troops--;
     }
     logging = "exectuting the order Advance for player  "+ *owner->m_name;
     Notify(this);
     if (troops == 0) {
         currentCommand->setEffect("Player " + *owner->m_name + " could not conquer Territory :" + *Desti->m_name + "and left " + std::to_string(*Desti->armies) + " units"  );
         
         cout << "Player " << *owner->m_name << " could not conquer Territory :" << *Desti->m_name << "and left " << *Desti->armies << " units" << endl;
         return true;
     }
     else {

         Player* Opponent = owner->getplayer(owner->AllPlayers, *Desti->player_owner);

         Opponent->RemoveTerritory(*Desti->player_owner);
         owner->territories.insert(owner->territories.begin(), Desti);

         Desti->player_owner = owner->m_name;
         *Desti->armies = troops;
         currentCommand->setEffect("Player " + *owner->m_name + "  conquered Territory : " + *Desti->m_name + " and left " + std::to_string(*Desti->armies) + " units");

         cout << "Player " << *owner->m_name << "  conquered Territory : " << *Desti->m_name << " and left " << *Desti->armies << " units" << endl;
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
Bomb::Bomb(Player* p,  Territory* Destination,Command* c, LogObserver* l) : Order(p, c, l)
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
         currentCommand->setEffect("Cannot execute order Bomb  from player :" + *owner->m_name + " as player own territory : " + *Desti->m_name);

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
         currentCommand->setEffect("Cannot execute order Bomb  from player :" + *owner->m_name + " as player does not own territory that is adjacent to : " + *Desti->m_name);

         cout << "Cannot execute order Bomb  from player :" << *owner->m_name << " as player does not own territory that is adjacent to : " << *Desti->m_name << endl;
         return false;
     }

     return true;
}

 bool Bomb::execute() {
     if (!validate())
         return false;

     owner->Territory_to_defend.insert(owner->Territory_to_defend.begin(), Desti);
     *Desti->armies = *Desti->armies / 2;
     logging = "executing the order deploy for player  "+ *owner->m_name;
     Notify(this);
     currentCommand->setEffect(" player :" + *owner->m_name + " Bombarrded : " + *Desti->m_name );
     cout << " player :" << *owner->m_name << " Bombarrded : " << *Desti->m_name << " which leaves only " << *Desti->armies << " there" << endl;

     return true;
}

//*************BLOCKADE *******************
Blockade::Blockade()
{
    cout << "blockade is creating..." << endl;
    set_type_id(3);

}
Blockade::Blockade(Player* p, Territory* Destination,Command* c, LogObserver* l) : Order(p, c, l){
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
         currentCommand->setEffect("Cannot execute order Advance from player :" + *owner->m_name + " as player does not own territory : " + *Desti->m_name);
         cout << "Cannot execute order Advance from player :" << *owner->m_name << " as player does not own territory : " << *Desti->m_name << endl;
         return false;
     }
     return true;
}

 bool Blockade::execute() {
     if (!validate()) {
         return false;
     }
     owner->Territory_to_defend.insert(owner->Territory_to_defend.begin(), Desti);

      owner->RemoveTerritory(*Desti->player_owner);
      owner->Neutral->territories.insert(owner->Neutral->territories.begin(), Desti);
     *Desti->armies = *Desti->armies * 2;
     currentCommand->setEffect("blockade executed by : " + *owner->m_name + "  on  " + *Desti->m_name + " and has now "  + " and owned by neeutral");
     cout << "blockade executed by : " << *owner->m_name << "  on  " << *Desti->m_name << " and has now " << *Desti->armies << " and owned by neeutral";
     return true;
}

//**********airlift
Airlift::Airlift()
{
    cout << "airlift is creating..." << endl;
    set_type_id(4);

}
Airlift::Airlift(Player* p, Territory* Source, int t, Territory* Destination,Command* c, LogObserver* l) : Order(p, c, l)
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
         currentCommand->setEffect("Cannot execute order Airlift from player :" + *owner->m_name + " as player does not own territory : " + *Desti->m_name);
    
         cout << "Cannot execute order Airlift from player :" << *owner->m_name << " as player does not own territory : " << *Desti->m_name << endl;
         return false;
     }
      found = (std::find(owner->territories.begin(), owner->territories.end(), src) != owner->territories.end());
     if (!found) {
         currentCommand->setEffect("Cannot execute order Airlift from player :" + *owner->m_name + " as player does not own territory : "+ *src->m_name);
         cout << "Cannot execute order Airlift from player :" << *owner->m_name << " as player does not own territory : " << *src->m_name << endl;
         return false;
     }
     return true;
}

 bool Airlift::execute() {
     if (!validate()) {
         return false;
     }
     owner->Territory_to_defend.insert(owner->Territory_to_defend.begin(), Desti);
     
     logging = "executing the order airlift for player  " + *owner->m_name;
     Notify(this);

     *src->armies = *src->armies - troops;
     *Desti->armies = *Desti->armies + troops;
     currentCommand->setEffect("executing Airlift from " + *owner->m_name + "  on " + *src->m_name + " to " + *Desti->m_name + "of " );

     cout << "executing Airlift from " << *owner->m_name << "  on " << *src->m_name <<" to "<<*Desti->m_name << "of "<<troops<< endl;

     return true;
}


//************NEGOTIATE *************

Negotiate::Negotiate()
{
    cout << "negotiate is creating..." << endl;
    set_type_id(5);

}
Negotiate::Negotiate(Player* p, Player* negotiated,Command* c, LogObserver* l) : Order(p, c, l)
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
     if (*owner->m_name == *Negotiated->m_name) {

         cout << "Cannot execute order Negotiate from player :" << *owner->m_name << " as player cannot negociate with himself "<< endl;
         currentCommand->setEffect("Cannot execute order Negotiate from player :" + *owner->m_name + " as player cannot negociate with himself ");
         return false;
     }
     std::list<Territory*>::iterator itCont;
     bool isadjacent = false;
     for (itCont = Negotiated->Territory_to_attack.begin(); itCont != Negotiated->Territory_to_attack.end(); ++itCont) {
         if (*owner->m_name== *(*itCont)->player_owner) {
       cout << "Cannot execute order Negotiate from player :" << *owner->m_name << " as player :  "<< *Negotiated ->m_name<<"is attacking him" << endl;
       currentCommand->setEffect("Cannot execute order Negotiate from player :" + *owner->m_name + " as player :  " + *Negotiated->m_name + "is attacking him");
       return false;
         }
     }

     return true;
}

 bool Negotiate::execute() {
     if (!validate()) {
         return false;
     }

     logging = "executing the order negociate for player  " + *owner->m_name;
     Notify(this);
     Negotiated->CannotAttack.insert(Negotiated->CannotAttack.begin(), owner);
     owner->CannotAttack.insert(owner->CannotAttack.begin(), Negotiated);
     cout << "executing Negotiate from " << *owner->m_name << "  on " << *this->Negotiated->m_name << endl;
     currentCommand->setEffect("executing Negotiate from " + *owner->m_name + "  on " + *this->Negotiated->m_name);

     return true;
}

//*************order list*********************

void OrdersList::set_order_list(Order* an_order)
{
    order_list.push_back(an_order);
}
void OrdersList::addOrder(Order* an_order)
{
    order_list.insert(order_list.end(),an_order);
    logging = "the following order was created <" + *an_order->orderName + "> and has been placed in the order list of player <" + *an_order->owner->m_name + ">";
    Notify(this);
}
OrdersList::OrdersList()
{
    order_list = list<Order*>();
};


OrdersList::~OrdersList()
{

};

list<Order*> OrdersList::get_order_list()
{
    return order_list;
}

void OrdersList::remove(Order* oneOrder)
{
    std::list<Order*>::iterator it = order_list.begin();

    while (it != order_list.cend())
    {
        list<Order*>::iterator curr = it++;
        if ( (*curr)== oneOrder) {
            (*curr)->execute();
            order_list.erase(curr);
        }
    }


}





// assignment operator
OrdersList& OrdersList::operator=(const OrdersList& o) {
    order_list = list<Order*>(o.order_list);
    return *this;
};


// cout operator
ostream& operator<<(ostream& strm, const OrdersList& a) {
    return  strm << "Orders stream insertion operator" << endl;
}



string OrdersList::stringToLog()
{
    return logging;
}

// copy constructor
OrdersList::OrdersList(const OrdersList& d)
{
    order_list = list<Order*>(d.order_list);
}