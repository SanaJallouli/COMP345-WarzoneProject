#pragma once 
#include "Map.hpp"
#include <list>
#include <iostream>
#include "CommandProcessing.h"

#include "Cards.hpp"
#include "Order.hpp"


using namespace std;

#include <stdio.h>
class Player{
    
    public :
        CommandProcessor* cP;
    string* m_name;
    list<Territory*> territories;
    list<Card*> cards;
    list<Order*> orders;
    Hand* hand;
    int* armies;
    int* deployed_inTurn;
    int* player_order;
list<Territory*> toDefend();
list<Territory*> toAttack();
list<Player*> CannotAttack;
list<Player*> AllPlayers;

list<Territory*> Territory_to_attackg;
bool recieve_card = false;

bool issueOrder();

void execDeploy();
    
  friend ostream& operator<<(ostream& strm, const Player& player);
Player& operator=(const Player &player);
    
Player(const Player &player);
    Player(string name);
Player();
~Player();
    
};



