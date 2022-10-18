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
     hand = new Hand(*(player.hand));
}

Player::Player(){
    m_name = new string();
    hand = new Hand();
     territories = list<Territory*>();;
     cards = list<Card*>();
     orders= list<Order*>();
}; //default constructor


Player::Player(string name){
    m_name = new string(name);
    hand = new Hand();
     territories = list<Territory*>();;
     cards = list<Card*>();
     orders= list<Order*>();
}; // constructor

Player::~Player() {
    delete m_name;//deallocate
    m_name = nullptr; // avoid dangling pointers
    delete hand;
    hand = nullptr;
    for (std::list<Territory*>::iterator it = territories.begin(); it != territories.end(); ++it) {
        delete *it;
        *it= nullptr;
    }
    for (std::list<Card*>::iterator it = cards.begin(); it != cards.end(); ++it) {
        delete *it;
        *it= nullptr;
    }
    for (std::list<Order*>::iterator it = orders.begin(); it != orders.end(); ++it) {
        delete *it;
        *it= nullptr;
    }

}

//cout operator
ostream& operator<<(ostream &strm, const Player& player) {
   return strm << "Player Name " << *player.m_name ;};

// assignment operator 
Player& Player::operator=(const Player &player)
 {
  
    this->m_name = new string(*player.m_name);
    this-> territories = list<Territory*>(player.territories);
    this->cards =  list<Card*>(player.cards);
    this->orders = list<Order*>(player.orders);
    this->hand = new Hand(*(player.hand));
   return *this;};


