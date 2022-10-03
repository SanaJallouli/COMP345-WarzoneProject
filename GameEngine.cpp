
#include <iostream>
#include "GameEngine.h"
using namespace std;
using MMM::MapLoader;

GameEngine::GameEngine() {
    state = "start";
    CommandProcessor* cp = new CommandProcessor();
}

void GameEngine:: readCommand(string){
    getCommand(string);
}

string GameEngine::getState(){
    return state;
}
void GameEngine::setState(string state1){
    this->state= state1;
    cout << "State has been changed to \"" << state1 << "\".";
}

GameEngine::GameEngine(const GameEngine){
    this->valid_commands
}

void GameEngine::transition(string state1) {
    setState(state1);
}






