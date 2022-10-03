#include "Order.h"

//Order&Order ::operator = (const Order&O)
//{
//
//}

Order::Order()
{
}

Order::~Order()
{
}
//Order::Order(const Order& O)
//{
//    this->vec_type1 = *new vector<string>(O.vec_type1);
//    this->type_id = new string(*(O.type_id));
//}
void Order::validate()
{
    cout << "validate if the order is valid" << endl;
    valid = true;
}

void Order::execute()
{
    if (valid) {
        cout << "executes the action..." << endl;
    }
}

void Order::set_type_id(int num)
{
    type_id = num;
}

string Order::get_type()
{
    return orders.at(type_id);
}





void OrdersList::set_order_list(Order* an_order)
{
    vec_order_list.push_back(an_order); //add an order
}

vector<Order*>* OrdersList::get_order_list()
{
    return &vec_order_list;
}

void OrdersList::remove(Order* oneOrder)
{
    for (int i = 0; i < vec_order_list.size(); i++) {
        if (oneOrder->get_type() == vec_order_list.at(i)->get_type()) {
            cout << "deleting the order : " << oneOrder->get_type() << endl;
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

Deploy::Deploy()
{
    cout << "deploy is creating..." << endl;
    set_type_id(0);
    string orderName="deploy";
}

Deploy::~Deploy()
{
}

string* Deploy::get_type()
{
    return &type;
}

Advance::Advance()
{
    cout << "advance is creating..." << endl;
    set_type_id(1);
    string orderName="advance";
}

Advance::~Advance()
{
}
string* Advance::get_type()
{
    return &type;
}
Bomb::Bomb()
{
    cout << "bomb is creating..." << endl;
    set_type_id(2);
    string orderName="bomb";
}

Bomb::~Bomb()
{
}
string* Bomb::get_type()
{
    return &type;
}
Blockade::Blockade()
{
    cout << "blockade is creating..." << endl;
    set_type_id(3);
    string orderName="blockade";
}

Blockade::~Blockade()
{
}
string* Blockade::get_type()
{
    return &type;
}
Airlift::Airlift()
{
    cout << "airlift is creating..." << endl;
    set_type_id(4);
    string orderName="airlift";
}

Airlift::~Airlift()
{
}
string* Airlift::get_type()
{
    return &type;
}
Negotiate::Negotiate()
{
    cout << "negotiate is creating..." << endl;
    set_type_id(5);
    string orderName="negotiate";
}

Negotiate::~Negotiate()
{
}
string* Negotiate::get_type()
{
    return &type;
}
