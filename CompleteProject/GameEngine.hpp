#include <ostream>
#include <list>
#include <string>
#include <iostream>
#include <string>
#include "Map.hpp"
#include "Player.hpp"
#include "CommandProcessing.h"

using namespace std ;
class State;
class GameEngine : public ILoggable, public Subject {
public:
    CommandProcessor* Cp;
    string logging;    string stringToLog() override;
    GameEngine(); // constructor
    ~GameEngine(); // distractor
    Map* map;
    Deck* deck;
    Command* currentCommand;
// list of all potential commands
    std::list<string*> command_list;
//list of all potenetial states
    std::list<State*> all_states;
    std::list<Player*> all_players;
// the current state of the game
    State* current_state;
    Player* NeutralPlayer;
    //return the state based on the command entered by user
    State* getstate(string name);
    string loadmap(string s);
    string add_player(string s);
    string Gamestart();
    string issueOrderPhase();
    string executeOrderPhase();
    string transitionInGame(string com, string arg);
    //read the command from the user
    string getcommand();
    //validate the command
    bool check_command(string s);
    void mainGameLoop();
    //the game loop
    void  manage();
    // display a list of possible commands to the user
    string listPossibilities();
    void StartupPhase();
    string assignArmy(Player* p);
    void endTurnPhase();
    string reinforcementPhase();
    // handle the transition from state to state depending on the commande
    string transition(string com, string arg);
    LogObserver* lo;
    //cout operator
    friend ostream& operator<<(ostream& strm, const GameEngine& engine);
    
    // copie constructor
    GameEngine(const GameEngine &g);
    
    // assignment operator
    GameEngine& operator=(const GameEngine &g);
};
//***************STATE ***********
class State {
public:
    State(); // default constructor
    State(string name); // constructor
    ~State(); // destructor
  
    string* name; // name of the state
    string* possible_action[3]; // the potential transitions command it accepts
    State* possible_states[3]; // the potential states it eventually gets to

    // add the possible states passed as argument to the possible state array
    void addpossible_state(State* s1, State* s3, State* s2);
    
    // add the possible commands passed as argument to the possible action  array
    void addpossible_action(string s1, string s3, string s2);

    // cout operator
    friend ostream& operator<<(ostream& strm, const State& State);
    
    
    // copy constructor
    State(const State &s);
    
    // assignment operator
    State& operator=(const State &s);

};
