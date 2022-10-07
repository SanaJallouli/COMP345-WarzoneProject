
#include <iostream>
#include "GameEngine.hpp"
#include "Map.h"

using namespace std;
//using MMM::MapLoader;

GameEngine::GameEngine() {
    state = "start";
    CommandProcessor* cp = new CommandProcessor();
}

void GameEngine:: readCommand(string s){
  //  getCommand(s);
}

string GameEngine::getState(){
    return state;
}
void GameEngine::setState(string state1){
    this->state= state1;
    cout << "State has been changed to \"" << state1 << "\".";
}

GameEngine::GameEngine(const GameEngine &g){
//    this->valid_commands;
}

void GameEngine::transition(string state1) {
    setState(state1);
}






