#pragma once 
#include "Map.hpp"
#include <list>
#include <iostream>
#include "CommandProcessing.h"

#include "Cards.hpp"
#include "Order.hpp"


using namespace std;
class OrdersList;
#include <stdio.h>
class Player{
    
    public :
        LogObserver* lo;
        Command* currentCommand;
        CommandProcessor* cP;
    string* m_name;
    list<Territory*> territories;
    list<Card*> cards;

    Hand* hand;
    int* armies;
    int* deployed_inTurn;
    int* player_order;
list<Territory*> toDefend();
list<Territory*> toAttack();
void RemoveTerritory(string teri_name);
Player* getplayer(list<Player*> l, string card_name);
std::list<Territory*> getAllTerritories(list<Player*> l);
list<Player*> CannotAttack;
list<Player*> AllPlayers;
Player* Neutral;
OrdersList* orders ;
list<Territory*> Territory_to_attack;
list<Territory*> Territory_to_defend;
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



