#include "GameEngine.h"


GameEngine::GameEngine()
{
    state* start = new state("start");
    current_state = start;
    state* maploaded = new state("maploaded");
    state* mapvalidated = new state("mapvalidated");
    state* playersadded = new state("playersadded");
    state* assignreinforcement = new state("assignreinforcement");
    state* issueorders = new state("issueorders");
    state* executeorders = new state("executeorders");
    state* win = new state("win");

    start->addpossible_action("loadmap", "", "");
    maploaded->addpossible_action("loadmap", "validatemap", "");
    mapvalidated->addpossible_action("addplayer", "", "");
    playersadded->addpossible_action("addplayer", "assigncountries", "");
    assignreinforcement->addpossible_action("issueorder", "", "");
    issueorders->addpossible_action("issueorder", "endissueorders", "");
    executeorders->addpossible_action("execorder", "endexecorders", "win");
    win->addpossible_action("end", "play", "");


    start->addpossible_state(maploaded, nullptr, nullptr);
    maploaded->addpossible_state(maploaded, mapvalidated, nullptr);
    mapvalidated->addpossible_state(playersadded, nullptr, nullptr);
    playersadded->addpossible_state(playersadded, assignreinforcement, nullptr);
    assignreinforcement->addpossible_state(issueorders, nullptr, nullptr);
    issueorders->addpossible_state(issueorders, executeorders, nullptr);
    executeorders->addpossible_state(executeorders, win, assignreinforcement);
    win->addpossible_state(start, nullptr, nullptr);
    
    all_states.insert(all_states.begin(), start);
    all_states.insert(all_states.begin(), maploaded);
    all_states.insert(all_states.begin(), mapvalidated);
    all_states.insert(all_states.begin(), playersadded);
    all_states.insert(all_states.begin(), assignreinforcement);
    all_states.insert(all_states.begin(), issueorders);
    all_states.insert(all_states.begin(), executeorders);
    all_states.insert(all_states.begin(), win);



}
state* GameEngine::getstate(string name) {
    std::list<state*>::iterator it;
    for (it = all_states.begin(); it != all_states.end(); ++it) {

        if (name == *(*it)->name) {
            return (*it);
        }
    }
    return nullptr;
}

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
        // check fi the maps was loaded or it failed : 
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
            current_state = getstate("playersadded");
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
        string final = ""; // will be filled later when  adding orders 
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
        return "ending the game\n";// 
    }
    else
        return "command not found please check possibilities\n";
}
string GameEngine::getcommand()
{
    string s;
    std::getline(std::cin, s);
    return s;
}
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

string  GameEngine::listPossibilities() {
    string possible="";
    for (int i = 0; i < 3; i++) {
      
        possible +=*current_state->possible_action[i]+" ";
    }
 
    return possible;
}
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

    }
}
ostream& operator<<(ostream& strm, const GameEngine& engine)
{
	// TODO: insert return statement here
    return strm << "current state is : " << engine.current_state;
}


state::state(string name)
{
    this->name = new string(name);

}
void state::addpossible_state(state* s1, state* s3, state* s2)
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
