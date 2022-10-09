#include "Order.hpp"


Order::Order()
{
 type_id =new int();
 valid = new bool();
}


Order::~Order()
{
    delete valid;
    valid = nullptr;
    
    delete type_id;
    type_id= nullptr;

}

Order::Order(const Order& O)
{
    orders =  vector<string*> (O.orders);
    type_id= new int(*type_id);
    valid = new bool(*O.valid);
    orderName = new string(* O.orderName);
}

Order& Order::operator=(const Order &O) {
    orders =  vector<string*> (O.orders);
    type_id= new int(*type_id);
    valid = new bool(*O.valid);
    orderName = new string(* O.orderName);
    return *this;
}

ostream& operator<<(ostream& strm, const Order& O){
    return strm << "Order : " << O.orderName ;}


void Order::validate()
{
    cout << "validate if the order is valid" << endl;
    *valid = true;
}

void Order::execute()
{
    if (*valid) {
        cout << "executes the action..." << endl;
    }
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
    orderName= new string("deploy");
}

Deploy::~Deploy()
{
}
//copy constructor

Deploy::Deploy(const Deploy& d) : Order (d)
{
    type = new string(*(d.type));
}
// assignment operator
Deploy& Deploy::operator=(const Deploy &d){
    Order : operator = (d);
    type = new string(*(d.type));
    return *this;
};

// cout operator
ostream& operator<<(ostream& strm, const Deploy& d) {
      return strm << "TYPE : " << d.type ;
};

string* Deploy::get_type()
{
    return type;
}



//**************ADVANCE *****************
Advance::Advance()
{
    cout << "advance is creating..." << endl;
    set_type_id(1);
    orderName=new string("advance");
}

Advance::~Advance()
{
}

string* Advance::get_type()
{
    return type;
}

Advance& Advance::operator=(const Advance &a){
    Order : operator = (a);
    type = new string(*(a.type));
    return *this;
};


Advance::Advance(const Advance& d) : Order (d)
{
    type = new string(*(d.type));
}
// cout operator
ostream& operator<<(ostream& strm, const Advance& a) {
      return strm << "TYPE : " << a.type ;}

//***************BOMB ******************
Bomb::Bomb()
{
    cout << "bomb is creating..." << endl;
    set_type_id(2);
    orderName=new string("bomb");
}


Bomb::~Bomb()
{
}

string*  Bomb::get_type()
{
    return type;
}


Bomb& Bomb::operator=(const Bomb &B){
    Order : operator = (B);
    type = new string(*(B.type));
    return *this;
};

Bomb::Bomb(const Bomb& d) : Order (d)
{
    type = new string(*(d.type));
}

// cout operator
ostream& operator<<(ostream& strm, const Bomb& a) {
      return strm << "TYPE : " << a.type ;}

//*************BLOCKADE *******************
Blockade::Blockade()
{
    cout << "blockade is creating..." << endl;
    set_type_id(3);
     orderName= new string("blockade");
}

Blockade::~Blockade()
{
}
string* Blockade::get_type()
{
    return type;
}

Blockade& Blockade::operator=(const Blockade &B){
    Order : operator = (B);
    type = new string(*(B.type));
    return *this;
};

Blockade::Blockade(const Blockade& d) : Order (d)
{
    type = new string(*(d.type));
}


// cout operator
ostream& operator<<(ostream& strm, const Blockade& a) {
      return strm << "TYPE : " << a.type ;}


//**********airlift
Airlift::Airlift()
{
    cout << "airlift is creating..." << endl;
    set_type_id(4);
    orderName= new string("airlift");
}

Airlift::~Airlift()
{
}
string* Airlift::get_type()
{
    return type;
}

Airlift& Airlift::operator=(const Airlift &a){
    Airlift : operator = (a);
    type = new string(*(a.type));
    return *this;
};


Airlift::Airlift(const Airlift& d) : Order (d)
{
    type = new string(*(d.type));
}
// cout operator
ostream& operator<<(ostream& strm, const Airlift& a) {
      return strm << "TYPE : " << a.type ;}




//************NEGOTIATE *************
Negotiate::Negotiate()
{
    cout << "negotiate is creating..." << endl;
    set_type_id(5);
    orderName=new string("negotiate");
}

Negotiate::~Negotiate()
{
}
string* Negotiate::get_type()
{
    return type;
}


// assignment operator
Negotiate& Negotiate::operator=(const Negotiate &a){
    Negotiate : operator = (a);
    type = new string(*(a.type));
    return *this;
};



// cout operator
ostream& operator<<(ostream& strm, const Negotiate& a) {
      return strm << "TYPE : " << a.type ;}


Negotiate::Negotiate(const Negotiate& d) : Order (d)
{
    type = new string(*(d.type));
}


//*************order list*********************

void OrdersList::set_order_list(Order* an_order)
{
    vec_order_list.push_back(an_order);
}

OrdersList::OrdersList()
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
        cout<<"moved succeessfully"<<endl;
    }
    else if (new_position == vec_order_list.size()  )
    {
        vec_order_list.push_back(vec_order_list.at(position));
        vec_order_list.erase(vec_order_list.begin() + position);
        cout<<"moved succeessfully"<<endl;
    }
    else {
        cout << "not valid position" << endl;
    }
}

// assignment operator
OrdersList& OrdersList::operator=(const OrdersList &o){
    vec_order_list = vector<Order*>(o.vec_order_list);
    return *this;
};


// cout operator
ostream& operator<<(ostream& strm, const OrdersList& a) {
  return  strm << "Orders stream insertion operator"<<endl;
    }



// copy constructor
OrdersList::OrdersList(const OrdersList& d)
{
    vec_order_list =  vector<Order*>(d.vec_order_list);
}
