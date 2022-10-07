#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include "Player.hpp"
#include "MapLoader.h"
using std::cout;
using std ::string;
using namespace std;

class GameEngine{
private:
    string state;
    void loadMap();
    void gameStart();
    void setState(string);
public:
    GameEngine();
    GameEngine(string);
    ~GameEngine();
    string getState();
    GameEngine(const GameEngine &g1);
    void transition(string);
    void readCommand(string);
    void testGameStates();
    
};
class Command{
private:
   // std::Command;
public:
  //  setCommand(std::string);
};
class CommandProcessor {
private:
   // std::cin<<std::pair<std::string, std::pair<std::string, std::string>>> valid_commands_and_their_transitions;
   // std::cin<<std::string> possible_valid_commands;
   // std::cin<<Command*> commands;
   // std::cin<<Command*> readCommand();
public:
    CommandProcessor();
    void getCommand(std::string);
};

