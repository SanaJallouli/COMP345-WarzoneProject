#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "PLayer.hpp"
using namespace std;

class Order
{
public:
    string* orderName;

    Order();
    Order(Player* player);
    virtual ~Order();
    string getResult();
    Command* c;
    //check of the oder is valid
   virtual bool validate()=0;
    //execute method
   virtual  bool execute() = 0;

    //set type of the subclass
    void set_type_id(int num);
    string* get_type();

    //copy constructor
    Order(const Order& O);

    // assignment operator
    Order& operator=(const Order& O);

    // cout operator
    friend ostream& operator<<(ostream& strm, const Order& order);
    int* type_id;
    Player* owner;
private:
    bool* valid;
    vector<string*> orders{ new string("deploy"), new string("advance"), new string("bomb") , new string("blockade"), new string("airlift"), new string("negotiate") };


};

//********** DEPLOY ***********

class Deploy : public Order
{

public:
    Deploy();// constructor
    Deploy(Player* p,int t,Territory* Destination);// constructor
    virtual ~Deploy(); // destructor

    string* get_type();

    bool validate() override;

    bool execute() override;

    //copy constructor
    Deploy(const Deploy& d);

    // assignment operator
    Deploy& operator=(const Deploy& d);

    // cout operator
    friend ostream& operator<<(ostream& strm, const Deploy& order);
    string* type = new string("deploy");
    int troops; 
    Territory* Desti;
private:

};

class Advance : public Order {
public:
    Advance();
    Advance(Player* p , Territory* Source, int t, Territory* Destination);
    virtual ~Advance();
    string* get_type();
    string* type = new string("advance");
    Territory* Desti;
    Territory* src;
    int troops;
    //copy constructor
    Advance(const Advance& d);
    bool validate() override;

    bool execute() override;
    Advance& operator=(const Advance& B);

    // cout operator
    friend ostream& operator<<(ostream& strm, const Advance& order);
private:

};



//******************BOMB ******************
class Bomb : public Order
{
public:
    Bomb();
    Bomb(Player* p, Territory* Destination);
    virtual ~Bomb();
    string* get_type();
    Territory* Desti;
    //copy constructor
    Bomb(const Bomb& d);

    // assignment operator
    Bomb& operator=(const Bomb& B);
    string* type = new string("bomb");
    bool validate() override;

    bool execute() override;


    // cout operator
    friend ostream& operator<<(ostream& strm, const Bomb& b);
private:

};


//***************blockade **********

class Blockade : public Order
{
public:
    Blockade();
    Blockade(Player* p, Territory* Destination);
    virtual ~Blockade();
    string* get_type();

    bool validate() override;

    bool execute() override;
    //copy constructor
    Blockade(const Blockade& d);

    // cout operator
    friend ostream& operator<<(ostream& strm, const Blockade& b);
    Territory* Desti;
    // assignment operator
    Blockade& operator=(const Blockade& B);
    string* type = new string("blockade");
private:

};



//*************AIRLIFT ************

class Airlift : public Order
{
public:
    Airlift();
    Airlift(Player* p, Territory* Source, int t, Territory* Destination);
    virtual ~Airlift();
    string* get_type();
    Territory* Desti;
    Territory* src;
    int troops; 
    // assignment operator
    Airlift& operator=(const Airlift& a);

    bool validate() override;

    bool execute() override;
    //copy constructor
    Airlift(const Airlift& d);


    string* type = new string("airlift");


    // cout operator
    friend ostream& operator<<(ostream& strm, const Airlift& b);
private:

};


// **************NEGOCIATE ************
class Negotiate : public Order
{
public:
    Negotiate();
    virtual ~Negotiate();
    string* get_type();
    string* type = new string("negotiate");
    Negotiate(Player* p, Player* negociated);
    
    //copy constructor
    Negotiate(const Negotiate& d);
    Player* Negotiated;
    // assignment operator
    Negotiate& operator=(const Negotiate& a);
    bool validate() override;

    bool execute() override;


    // cout operator
    friend ostream& operator<<(ostream& strm, const Negotiate& b);
private:

};


//*****************ORDER LIST **************
class OrdersList
{
public:

    OrdersList();
    ~OrdersList();


    void set_order_list(Order* an_order);
    vector<Order*> get_order_list();
    //delete an order
    void remove(Order* oneOrder);
    //move
    void move(int position, int new_position);

    //copy constructor
    OrdersList(const OrdersList& d);

    // cout operator
    friend ostream& operator<<(ostream& strm, const OrdersList& b);

    // assignment operator
    OrdersList& operator=(const OrdersList& O);
    vector<Order*> vec_order_list; //store the orders
private:

};