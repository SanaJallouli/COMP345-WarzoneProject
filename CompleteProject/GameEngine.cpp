#include "GameEngine.hpp"


// constructor
GameEngine::GameEngine()
{
    State* start = new State("start");
    current_state = start;
    State* maploaded = new State("maploaded");
    State* mapvalidated = new State("mapvalidated");
    State* playersadded = new State("playersadded");
    State* assignreinforcement = new State("assignreinforcement");
    State* issueorders = new State("issueorders");
    State* executeorders = new State("executeorders");
    State* win = new State("win");

// insert the possible commands in a list corresponding to each of the states
    start->addpossible_action("loadmap", "", "");
    maploaded->addpossible_action("loadmap", "validatemap", "");
    mapvalidated->addpossible_action("addplayer", "", "");
    playersadded->addpossible_action("addplayer", "assigncountries", "");
    assignreinforcement->addpossible_action("issueorder", "", "");
    issueorders->addpossible_action("issueorder", "endissueorders", "");
    executeorders->addpossible_action("execorder", "endexecorders", "win");
    win->addpossible_action("end", "play", "");

// insert in a list the possible states achievable from each of the states
    start->addpossible_state(maploaded, nullptr, nullptr);
    maploaded->addpossible_state(maploaded, mapvalidated, nullptr);
    mapvalidated->addpossible_state(playersadded, nullptr, nullptr);
    playersadded->addpossible_state(playersadded, assignreinforcement, nullptr);
    assignreinforcement->addpossible_state(issueorders, nullptr, nullptr);
    issueorders->addpossible_state(issueorders, executeorders, nullptr);
    executeorders->addpossible_state(executeorders, win, assignreinforcement);
    win->addpossible_state(start, nullptr, nullptr);
    
// storing all the states
    all_states.insert(all_states.begin(), start);
    all_states.insert(all_states.begin(), maploaded);
    all_states.insert(all_states.begin(), mapvalidated);
    all_states.insert(all_states.begin(), playersadded);
    all_states.insert(all_states.begin(), assignreinforcement);
    all_states.insert(all_states.begin(), issueorders);
    all_states.insert(all_states.begin(), executeorders);
    all_states.insert(all_states.begin(), win);

}

//return the state based on the command entered by user
State* GameEngine::getstate(string name) {
    std::list<State*>::iterator it;
    for (it = all_states.begin(); it != all_states.end(); ++it) {

        if (name == *(*it)->name) {
            return (*it);
        }
    }
    return nullptr;
}


//handle the transition from state to state depending on the commande

string  GameEngine::transition(string com,string arg)
{
    if (com == "addplayer") {
        // create player with the name arg and add it to the list of players
            string problem = "";
            if (arg == com) {
                problem = "player name empty";
            }


            if (problem == "") {
                current_state = getstate("playersadded");
                return "Player : " + arg + " was added! \n";
            }
            else
                return "Player cannot be added  : " + problem + "!\n";
    }

    else if (com == "loadmap") {
        // load map with arg as the path
        // check if the maps was loaded or it failed :
        if (arg == com ) {
            return "Map path  is empty \n";
        }
        string problem = "";//will change with the problem from the map
        if (problem == "") {
            current_state = getstate("maploaded");
            return "map  : " + arg + " was loaded! \n";
        }
        else
            return "Map with path " + arg + " does not exist : " + problem + " \n";
    }

    else if (com == "validatemap") {
        string problem = "";//will change with the return of the validate map->validate()
        if (problem == "") {
            current_state = getstate("mapvalidated");
            return "map  : " + arg/*map->m_name*/ + " is  valid! \n";
        }
        else
            return "Map with path " + arg + " has the following problem :  " + problem + " \n";
    }


    else if (com == "assigncountries") {

        string problem = "";//will change with the return of the validate
        string final = "final"; // will be filled later when  adding territories to player
        if (problem == "") {
            current_state = getstate("assignreinforcement");
            return "reinforcement assigned : " + final + '\n';
        }
        else
            return "failed to  assign territories : " + problem + '\n';


    }
    else if (com == "issueorder") {
        string problem = "";//will change with the return of the validate
        string final = ""; // will be filled later when adding orders
        if (problem == "") {
            current_state = getstate("issueorders");
            return "orders issued : " + final + '\n';
        }
        else
            return "failed to  issued orders : " + problem + "\n";

    }
    else if (com == "endissueorders") {
        current_state = getstate("executeorders");
        return "ending orders issued :\n";
    }

    else if (com == "execorder") {
        string problem = "";//will change with the return executing orders
        string final = ""; // will be filled later
        if (problem == "") {
            current_state = getstate("executeorders");
            return "orders executed : " + final + "\n";
        }
        else
            return "failed to  execute orders : " + problem + "\n";
    }
    else if (com == "endexecorders") {
        current_state = getstate("assignreinforcement");
        return "ending orders execution\n";
    }
    else if (com == "win") {
        current_state = getstate("win");
        return /*player name */ "won the game : \n"/*game resume */ ;
    }

    else if (com == "play") {
        current_state = getstate("start");
        return "Starting the game againt\n";
    }
    else if (com == "end") {
        current_state = getstate("end");
        return "end";//
    }
    else
        return "command not found please check possibilities\n";
}

//read the command from the user
string GameEngine::getcommand()
{
    string s;
    std::getline(std::cin, s);
    return s;
}

//validate the comand
bool GameEngine::check_command(string s){
    if (s == "") {
        return false;
    }
    for (int i = 0; i < 3; i++) {
        if (*(current_state->possible_action[i]) == s)
            return true;
    }
    return false;
}

// give the users the list of commands they can enter
string  GameEngine::listPossibilities() {
    string possible="";
    for (int i = 0; i < 3; i++) {
      
        possible +=*current_state->possible_action[i]+" ";
    }
 
    return possible;
}


//the game loop
void GameEngine::manage()
{
    string message = "";
    while (true) {

        cout << "current state is : " + *current_state->name<<endl;
        cout << "possible actions are : " + listPossibilities() << endl;
        string command = getcommand();
        string com, arg;
        com = string(command.substr(0, command.find(" ")));

        arg = command.substr(command.find(" ") + 1);
        if (!check_command(com)) {
            cout << "INVALID COMMAND \n";
        }
        else {
            message = transition(com, arg);
            cout << message;
        }
        if (message == "end"){return;}

    }
}

// cout operator
ostream& operator<<(ostream& strm, const GameEngine& engine)
{
    // TODO: insert return statement here
    return strm << "current state is : " << engine.current_state;
}

// copie constructor
GameEngine::GameEngine(const GameEngine &g){
    std::list<string*> command_list;
//list of all potenetial states
    std::list<State*> all_states;
// the current state of the game
    current_state = new State(*(g.current_state));
    all_states =  list<State*>(g.all_states);
    command_list =  list<string*>(g.command_list);
}
// assignment operator
GameEngine& GameEngine::operator=(const GameEngine &g)
 {
     
    std::list<string*> command_list;
//list of all potenetial states
    std::list<State*> all_states;
// the current state of the game
    current_state = new State(*(g.current_state));
    all_states =  list<State*>(g.all_states);
    command_list =  list<string*>(g.command_list);
       return *this;};



// destructor

GameEngine::~GameEngine(){
    
    delete current_state;
    current_state= nullptr;
    // the other data members are lists of pointers:
    // the list will be destroyed when out of scope
    // and the destructors of the pointer type will be used
        
}


//***********STATE *************

State::State(string name)
{
    this->name = new string(name);
    
}

// add the possible states passed as argument to the possible state array

void State::addpossible_state(State* s1,State* s3,State* s2)
{
    this->possible_states[0] = s1;
    this->possible_states[1] = s2;
    this->possible_states[2] = s3;

}

// add the possible commands passed as argument to the possible action  array

void State::addpossible_action(string s1, string s3, string s2)
{
    this->possible_action[0] = new string(s1);
    this->possible_action[1] = new string(s2);
    this->possible_action[2] = new string(s3);

}

// cout operator
ostream& operator<<(ostream& strm, const State& State){
    return strm << "current State is : " << State.name ;
}

// destructor
State::~State(){
    delete name;
    name= nullptr ;
    // the other data members are array of pointers :
    // the destructor of the type of pointer will be used
}

// cpy constructor
State::State(const State &s){
    name = new string (*(s.name));
     possible_action[0]  = new string(*(s.possible_action[0]));
     possible_action[1] = new string(*(s.possible_action[1]));
     possible_action[2] = new string(*(s.possible_action[2]));
  
  
  possible_states[0]  = new State(*(s. possible_states[0]));
  possible_states[1] = new State(*(s. possible_states[1]));
  possible_states[2] = new State(*(s. possible_states[2]));
}

// assignment operator
State& State::operator=(const State &s)
 {
      name = new string (*(s.name));
       possible_action[0]  = new string(*(s.possible_action[0]));
       possible_action[1] = new string(*(s.possible_action[1]));
       possible_action[2] = new string(*(s.possible_action[2]));
    
    
    possible_states[0]  = new State(*(s. possible_states[0]));
    possible_states[1] = new State(*(s. possible_states[1]));
    possible_states[2] = new State(*(s. possible_states[2]));

       return *this;};

