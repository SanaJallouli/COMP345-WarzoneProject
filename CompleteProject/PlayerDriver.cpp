#include "PlayerDriver.hpp"


    void testPlayers(){
        cout<< "******************** TEST PLAYER ******************* \n"<<endl;
        string name = "PLayer1";
        Player* player = new Player(name);
        player->territories.insert(player->territories.begin(), new Territory());
        player->toDefend();
        player->toAttack();
        // making sure copy constructor is deept copy
        // list pf territories are deep copy of pointers but are initialized to point to same cells 
        Player* player2 = new Player(*player) ;
        Territory* ter = new Territory();
        player->territories.insert( player->territories.begin(),ter);
        
    };



