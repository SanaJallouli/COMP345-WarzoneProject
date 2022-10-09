#pragma
#include <ostream>
#include <list>
#include <string>
#include <iostream>
#include "state.h"
using namespace std ;
class GameEngine {
public:
	GameEngine();
	~GameEngine();

	std::list<string*> command_list; 
	std::list<state*> all_states;
	state* current_state;
	state* getstate(string name);
	string getcommand();
	bool check_command(string s);
	void  manage();
	string listPossibilities();
	string transition(string com, string arg);
	friend ostream& operator<<(ostream& strm, const GameEngine& engine);
};