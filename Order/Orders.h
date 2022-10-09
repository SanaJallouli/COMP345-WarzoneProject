#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void testOrdersList();

class Order
{
public :
    Order();
    Order(string);
    ~Order();
    string getResult();

    //check of the oder is valid
    void validate();
    //execute method
    void execute();

    //set type of the subclass
    void set_type_id(int num);
    string get_type();

private :
    bool valid;
    vector<string> orders = { "deploy", "advance", "bomb", "blockade", "airlift", "negotiate" };
    int type_id;
    string orderName;
};

class Deploy : public Order
{

public:
    Deploy();
    ~Deploy();
    string* get_type();
private:
    string type = { "deploy" };
};

class Advance : public Order {
public:
    Advance();
    ~Advance();
    string* get_type();
private:
    string type = { "advance" };
};

class Bomb : public Order
{
public:
    Bomb();
    ~Bomb();
    string* get_type();
private:
    string type = { "bomb" };
};

class Blockade : public Order
{
public:
    Blockade();
    ~Blockade();
    string* get_type();
private:
    string type = { "blockade" };
};

class Airlift : public Order
{
public:
    Airlift();
    ~Airlift();
    string* get_type();
private:
    string type = { "airlift" };
};

class Negotiate : public Order
{
public:
    Negotiate();
    ~Negotiate();
    string* get_type();
private:
    string type = { "negotiate" };
};

class OrdersList
{
public:
    void set_order_list(Order* an_order);
    vector<Order*>* get_order_list();
    //delete an order
    void remove(Order* oneOrder);
    //move
    void move(int position, int new_position);

private:
    vector<Order*> vec_order_list; //store the orders
};
