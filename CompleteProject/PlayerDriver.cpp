#include "PlayerDriver.hpp"


    void testPlayers(){
        cout<< "******************** TEST PLAYER ******************* \n"<<endl;
        string name = "PLayer1";
        Player* player = new Player(name);
        player->toDefend();
        player->toAttack();
    };



