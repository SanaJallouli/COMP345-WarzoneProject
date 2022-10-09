#pragma
#include <ostream>
#include <list>
#include <string>
#include <iostream>
using namespace std ;

class state {
public:
	state();
	~state();

	string* name;
	string* possible_action[3];
	state* possible_states[3];

	state(string name);

	void addpossible_state(state* s1, state* s3, state* s2);

	void addpossible_action(string s1, string s3, string s2);
};

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