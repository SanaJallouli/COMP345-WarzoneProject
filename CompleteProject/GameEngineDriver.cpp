#pragma once
#include <iostream>
#include "GameEngine.hpp"

// free function to test the game states
void testGameStates()
{
    cout<< "******************** GAME ENGINE ******************* \n"<<endl;
    GameEngine* ge=new GameEngine() ;
    ge->StartupPhase();
    ge->mainGameLoop();
   
}

