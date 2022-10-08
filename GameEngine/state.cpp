#include "state.h"

state::state(string name)
{
	this->name = new string(name);
	
}
void state::addpossible_state(state* s1,state* s3,state* s2)
{
	this->possible_states[0] = s1;
	this->possible_states[1] = s2;
	this->possible_states[2] = s3;

}void state::addpossible_action(string s1, string s3, string s2)
{
	this->possible_action[0] = new string(s1);
	this->possible_action[1] = new string(s2);
	this->possible_action[2] = new string(s3);

}
