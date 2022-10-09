#pragma
#include <string>
using namespace std;
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