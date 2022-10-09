#pragma once 
#include "Map.hpp"
#include <list>
#include <iostream>
#include "Order.hpp"
#include "Cards.hpp"

using namespace std;


#include <stdio.h>
class Player{
    
    public :
    string* m_name;
    list<Territory*> territories;
    list<Card*> cards;
    list<Order*> orders;
  
    
list<Territory*> toDefend();
list<Territory*> toAttack();

void issueOrder();
    
  friend ostream& operator<<(ostream& strm, const Player& player);
Player& operator=(const Player &player);
    
Player(const Player &player);
    Player(string name);
Player();
~Player();
    
};



