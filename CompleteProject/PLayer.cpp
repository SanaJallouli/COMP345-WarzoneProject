#pragma once
#include "Player.hpp"
#include "Map.hpp"
#include "Cards.hpp"
#include "Order.hpp"
using namespace std;


list<Territory*> Player::toDefend(){
    cout<<"toDefend method working \n";
    Territory* terr = new Territory();
    list<Territory*> randomTerr;
    randomTerr.insert(randomTerr.begin(),terr);
    return randomTerr;
};


list<Territory*> Player::toAttack(){
    cout<<"toAttack method working \n";
    Territory* terr = new Territory();
    list<Territory*> randomTerr;
    randomTerr.insert(randomTerr.begin(),terr);
    return randomTerr;
};


void Player::issueOrder(){
        Order* order;
        order= new Order();
        orders.insert(orders.begin(),order);
        cout<<"issueOrder method working \n this is the order created: "<<order<<endl;
    }

 Player::Player(const Player& player){
     m_name = new string(*player.m_name);
     territories = list<Territory*>(player.territories);
     cards =  list<Card*>(player.cards);
     orders = list<Order*>(player.orders);
}

Player::Player(){

}; //default constructor


Player::Player(string name){
    m_name = new string(name);
}; //default constructor

Player::~Player() {
    delete m_name;//deallocate
    m_name = nullptr; // avoid dangling pointers
// the other data members are lists of pointers
// the lists are from the std so they will be deleted automatically
// the content of the list are pointers, so the proper distructors will be called when the lists goes out of scope

}

//cout operator
ostream& operator<<(ostream &strm, const Player& player) {
   return strm << "Player Name " << *player.m_name ;};

// assignment operator 
Player& Player::operator=(const Player &player)
 {
   m_name = new string(*player.m_name);
   territories = list<Territory*>(player.territories);
   cards =  list<Card*>(player.cards);
   orders = list<Order*>(player.orders);
   return *this;};


