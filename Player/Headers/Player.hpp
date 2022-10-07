//
//  Player.hpp
//  comp345part2
//
//  Created by Sana Jallouli on 2022-10-01.
//
#include "Map.h"
#include <list>
#include "Orders.h"
#include "Cards.h"
using namespace std;
#ifndef Player_hpp
#define Player_hpp

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
#endif /* Player_hpp */

