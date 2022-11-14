#include "GameEngine.hpp"


Player* getPlayer(list<Player*> lt,string name) {
    std::list<Player*>::iterator it;
    for (it = lt.begin(); it != lt.end(); ++it) {

        if (name == *(*it)->m_name) {
            return (*it);
        }
    }
    return nullptr;

}
Player* getPlayer(list<Player*> lt, int name) {
    std::list<Player*>::iterator it;
    for (it = lt.begin(); it != lt.end(); ++it) {

        if (name == *(*it)->player_order) {
            return (*it);
        }
    }
    return nullptr;

}
string GameEngine::stringToLog()
{
    return logging;
}
// constructor
GameEngine::GameEngine(bool fromfile)
{
    lo = new LogObserver();
    Attach(lo);
    if (fromfile)
    Cp = new CommandProcessorAdapter(new FileLineReader(), "C:\\Users\\bechr\\Documents\\GitHub\\COMP345-WarzoneProject\\all\\working\\1.txt", lo);
    else 
        Cp = new CommandProcessor( lo);

    State* start = new State("start");
    current_state = start;
    State* maploaded = new State("maploaded");
    State* mapvalidated = new State("mapvalidated");
    State* playersadded = new State("playersadded");
    State* gamestart = new State("gamestart");
    State* assignreinforcement = new State("assignreinforcement");
    State* issueorders = new State("issueorders");
    State* executeorders = new State("executeorders");
    State* win = new State("win");
    deck = new Deck(50);
    NeutralPlayer = new Player("NEUTRAL");
    // insert the possible commands in a list corresponding to each of the states
    start->addpossible_action("loadmap", "", "");

    maploaded->addpossible_action("loadmap", "validatemap", "");
    mapvalidated->addpossible_action("addplayer", "", "");
    playersadded->addpossible_action("addplayer", "gamestart", "");

    gamestart->addpossible_action("", "", "");
    assignreinforcement->addpossible_action("issueorder", "", "");
    issueorders->addpossible_action("issueorder", "endissueorders", "");
    executeorders->addpossible_action("execorder", "endexecorders", "win");
    win->addpossible_action("end", "play", "");

    // insert in a list the possible states achievable from each of the states
    start->addpossible_state(maploaded, nullptr, nullptr);
    maploaded->addpossible_state(maploaded, mapvalidated, nullptr);
    mapvalidated->addpossible_state(playersadded, nullptr, nullptr);
    playersadded->addpossible_state(playersadded, assignreinforcement, nullptr);
    gamestart->addpossible_state(nullptr, nullptr, nullptr);

    assignreinforcement->addpossible_state(issueorders, nullptr, nullptr);
    issueorders->addpossible_state(issueorders, executeorders, nullptr);
    executeorders->addpossible_state(executeorders, win, assignreinforcement);
    win->addpossible_state(start, nullptr, nullptr);

    // storing all the states
    all_states.insert(all_states.begin(), start);
    all_states.insert(all_states.begin(), maploaded);
    all_states.insert(all_states.begin(), mapvalidated);
    all_states.insert(all_states.begin(), playersadded);
    all_states.insert(all_states.begin(), gamestart);
    all_states.insert(all_states.begin(), assignreinforcement);
    all_states.insert(all_states.begin(), issueorders);
    all_states.insert(all_states.begin(), executeorders);
    all_states.insert(all_states.begin(), win);

}
GameEngine::GameEngine()
{
    lo = new LogObserver();
    Attach(lo);
    Cp = new CommandProcessorAdapter(new FileLineReader(),"C:\\Users\\bechr\\Documents\\GitHub\\COMP345-WarzoneProject\\all\\working\\1.txt",lo);
    State* start = new State("start");
    current_state = start;
    State* maploaded = new State("maploaded");
    State* mapvalidated = new State("mapvalidated");
    State* playersadded = new State("playersadded");
    State* gamestart = new State("gamestart");
    State* assignreinforcement = new State("assignreinforcement");
    State* issueorders = new State("issueorders");
    State* executeorders = new State("executeorders");
    State* win = new State("win");
    deck = new Deck(50);
    NeutralPlayer = new Player("NEUTRAL");
// insert the possible commands in a list corresponding to each of the states
    start->addpossible_action("loadmap", "", "");

    maploaded->addpossible_action("loadmap", "validatemap", "");
    mapvalidated->addpossible_action("addplayer", "", "");
    playersadded->addpossible_action("addplayer", "gamestart", "");

    gamestart->addpossible_action("", "", "");
    assignreinforcement->addpossible_action("issueorder", "", "");
    issueorders->addpossible_action("issueorder", "endissueorders", "");
    executeorders->addpossible_action("execorder", "endexecorders", "win");
    win->addpossible_action("end", "play", "");

// insert in a list the possible states achievable from each of the states
    start->addpossible_state(maploaded, nullptr, nullptr);
    maploaded->addpossible_state(maploaded, mapvalidated, nullptr);
    mapvalidated->addpossible_state(playersadded, nullptr, nullptr);
    playersadded->addpossible_state(playersadded, assignreinforcement, nullptr);
    gamestart->addpossible_state(nullptr, nullptr, nullptr);

    assignreinforcement->addpossible_state(issueorders, nullptr, nullptr);
    issueorders->addpossible_state(issueorders, executeorders, nullptr);
    executeorders->addpossible_state(executeorders, win, assignreinforcement);
    win->addpossible_state(start, nullptr, nullptr);
    
// storing all the states
    all_states.insert(all_states.begin(), start);
    all_states.insert(all_states.begin(), maploaded);
    all_states.insert(all_states.begin(), mapvalidated);
    all_states.insert(all_states.begin(), playersadded);
    all_states.insert(all_states.begin(), gamestart);
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

string  GameEngine::loadmap(string s) {

    MapLoader* LOADER = new MapLoader();
    string problem = "";
    problem = LOADER->ReadDescription("C:\\Users\\bechr\\Documents\\GitHub\\COMP345-WarzoneProject\\all\\working\\map.txt");

    if (problem != "")
        return problem; 
             LOADER->LoadMap();
             map = LOADER->m_map;
   return problem;
}

string GameEngine::add_player(string s ) {
    if (getPlayer(all_players, s) != nullptr) {
        return "Player already exist";
    }
    Player* p = new Player(s);
    p->cP = Cp;
    all_players.insert(all_players.begin(),p);
    return "";
}


string GameEngine::Gamestart() {
    //random order of player 

    int nbr_player = all_players.size();
    std::list<Player*>::iterator i_player;
    ((*all_players.begin())->player_order) =new int( (1 /*std::rand() */ % (nbr_player)) + 1);
    int i = *((*all_players.begin())->player_order);
    //cout <<i<<endl<< nbr_player<<endl;
    for (i_player = all_players.begin(); i_player != all_players.end(); ++i_player) {
        i++;
        (*i_player)->player_order = new int((i % (nbr_player))+1);
      
        //cout << *(*i_player)->m_name << "    " << *(*i_player)->player_order<<endl;
    }


   // distribute territories 

    list<Territory*> temp =  list<Territory*>(map->m_Territories);
   
    std::list<Territory*>::iterator it;
    
    int selectedplayer;
    int j = 0;
    while (temp.size()!=0)
         {   
            selectedplayer = (j % nbr_player) + 1;
            int selected = 1/*rand()*/ % temp.size();
            i = 0;
            int k = 0;


            for (it = temp.begin(); it != temp.end(); ++it) {
                
                if (i == selected) {
                    Player* p = getPlayer(all_players, selectedplayer);
                    (*it)->player_owner = new string(*(p->m_name));
                    p->territories.insert(p->territories.begin(), *it);
                    temp.remove(*it);
                    j++;
                    break;
                }
                i++;

            }
       }

// Distribute armies
    for (i = 0; i < all_players.size(); i++) {
        Player* p = getPlayer(all_players, i+1);
        p->armies = new int(50);
    }





  //  cout << temp.size()<<endl; 
  //  cout << map->m_Territories.size()<<endl;
    //
    return "";
}
//handle the transition from state to state depending on the commande

string  GameEngine::transition(string com, string arg)
{
    if (com == "addplayer") {
        // create player with the name arg and add it to the list of players

        string problem = "";
        if (arg == com) {
            problem = "player name empty";

            currentCommand->setEffect("player name empty cannot add him");
            return problem;
        }
        if ((all_players).size() == 6) {

            currentCommand->setEffect("Maximum number of player reached cant add more player");
            return "Maximum number of player reached cant add more player";
        }

        problem = add_player(arg);

        if (problem == "") {
            logging = "playersadded still staying in this state";
            Notify(this);
            current_state = getstate("playersadded");
            currentCommand->setEffect("Player : " + arg + " was added! \n");
            return "Player : " + arg + " was added! \n";
        }
        else {

            currentCommand->setEffect("Player cannot be added  : " + problem + "!\n");

            return "Player cannot be added  : " + problem + "!\n";
        }
    }

    else if (com == "loadmap") {
        // load map with arg as the path
        // check if the maps was loaded or it failed :
        if (arg == com) {

            currentCommand->setEffect("Map path  is empty \n");
            return "Map path  is empty \n";
        }
        string problem = loadmap(arg);//will change with the problem from the map

        if (problem == "") {
            logging = "map was loaded  going to state map loaded";
            Notify(this);
            current_state = getstate("maploaded");
            currentCommand->setEffect("map  : " + arg + " was loaded! \n");
            return "map  : " + arg + " was loaded! \n";
        }
        else {
            currentCommand->setEffect("Map with path " + arg + " does not exist : " + problem + " \n");

            return "Map with path " + arg + " does not exist : " + problem + " \n";
        }
    }

    else if (com == "validatemap") {
        string problem = "";//will change with the return of the validate map->validate()
        problem = map->Validate();
        if (problem == "") {
            logging = "map was validated  going to state addplayer";
            Notify(this);
            current_state = getstate("mapvalidated");
            currentCommand->setEffect("map  : " + arg/*map->m_name*/ + " is  valid! \n");

            return "map  : " + arg/*map->m_name*/ + " is  valid! \n";
        }
        else {
            currentCommand->setEffect("Map with path " + arg + " has the following problem :  " + problem + " \n");

            return "Map with path " + arg + " has the following problem :  " + problem + " \n";
        }
    }




    /// GAMEPHASE 
    else if (com == "gamestart") {


        if (all_players.size() < 2) {
            currentCommand->setEffect("cannot start game there is not enough players : \n");

            return "cannot start game there is not enough players : \n";
        }

        string problem = Gamestart();
        if (problem != "") {

            currentCommand->setEffect("failed to  assign territories : " + problem + '\n');

            return "failed to  assign territories : " + problem + '\n';
        }
        logging = "going to state gamestart ";
        Notify(this);
        current_state = getstate("gamestart");
        currentCommand->setEffect("\nTHE GAME HAS STARTED :\n");

        return "\nTHE GAME HAS STARTED :\n";
    }

}

string GameEngine::issueOrderPhase() {
    while (true) {
        bool end = false;
        for (int i = 1; i < all_players.size() + 1; i++) {
            ;
            Player* p = getPlayer(all_players, i);
            bool val = p->issueOrder();
           end= end || !val;
        }
        if (end == true) {
            break;
        }
    }
    return "";
}

string GameEngine::executeOrderPhase() {
    for (int i = 1; i < all_players.size() + 1; i++) {
        ;
        Player* p = getPlayer(all_players, i);
        cout << "\n Player :" << *p->m_name << "  executing Deploy order " << endl;
        p->execDeploy();
    }
    int ordercount = 0;
    while (true) {
        int all_orders = 0;
        for (int i = 1; i < all_players.size() + 1; i++) {

            Player* p = getPlayer(all_players, i);
            cout << "\n Player :" << *p->m_name << "  executing order " << ordercount << endl;
            if (p->orders->order_list.size() != 0) {
                p->orders->order_list.front()->execute();
                p->orders->order_list.erase(p->orders->order_list.begin());
                all_orders += p->orders->order_list.size();
            }

        }
        if (all_orders == 0) {
                break;
        }
        ordercount++;
    }
    return "";
}
string  GameEngine::transitionInGame(string com, string arg){
    // REMOOOVE  // REMOOOVE 
  

    // REMOOOVE  // REMOOOVE 
    ///ISSUE ORDER 

     if (*current_state->name == "issueorders") {

         currentCommand->setEffect("start issueorder phase");

        string problem =issueOrderPhase();;
        string final = ""; // will be filled later when adding orders
        if (problem == "") {
            logging = "going to state finished issuing orders going in state executeorder ";
            Notify(this);
            current_state = getstate("executeorders");
            return "orders issued : "  + '\n';
        }
        else {
            currentCommand->setEffect("failed start issueorder phase");

            return "failed to  issued orders : " + problem + "\n";
        }
    }


    else if (*current_state->name == "executeorders") {
         currentCommand->setEffect(" start execute order phase");

        string problem = executeOrderPhase();

        if (problem == "") {
            logging = "going to state finished executing orders going in state assignreinforcement ";
            Notify(this);
            current_state = getstate("assignreinforcement");
            return "orders executed : \n";
        }
        else
            return "failed to  execute orders : " + problem + "\n";
    }

    else if (*current_state->name == "win") {
         logging = "going to state win ";
         Notify(this);
        current_state = getstate("win");
        return /*player name */ "won the game : \n"/*game resume */ ;
    }

    else if (com == "play") {
                  logging = "going to state play ";
         Notify(this);
        current_state = getstate("start");
        currentCommand->setEffect(" started another game");

        return "Starting the game againt\n";
    }
    else if (com == "end") {
         currentCommand->setEffect(" ended another game");

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

void GameEngine::StartupPhase() {
    while (true) {
        string message = "";
        cout << "current state is : " + *current_state->name << endl;
        cout << "possible actions are : " + listPossibilities() << endl;
  
      currentCommand =Cp->getCommand();


        string com, arg;
        com = string(currentCommand->getCommand().substr(0, currentCommand->getCommand().find(" ")));

        arg = currentCommand->getCommand().substr(currentCommand->getCommand().find(" ") + 1);
        if (!check_command(com)) {
            cout << "INVALID COMMAND \n";
        }
        else {
            message = transition(com, arg);
            cout << message;
        }
        if (*(current_state->name) == "gamestart") {
            
            for (int i = 1; i < all_players.size() + 1; i++) {
                Player* p = getPlayer(all_players, i);
                p->AllPlayers = all_players;
                p->Neutral = NeutralPlayer;
                p->lo = lo;
            }
            return; }
    }
}


string GameEngine::assignArmy(Player* p ) {

    if (p->territories.size() / 3 > 3)
        *p->armies = *p->armies + p->territories.size() / 3;
    else
        *p->armies = *p->armies + 3;

 
    return "";
}
void GameEngine::endTurnPhase() {
    cout << "starting TURN PHASE " << endl;
    for (int i = 1; i < all_players.size() + 1; i++) {
        Player* p = getPlayer(all_players, i);
        p->CannotAttack.clear();
        p->Territory_to_attack.clear();
        p->Territory_to_defend.clear();
   
        p->hand->addCardHand(deck->draw());
        if (p->recieve_card) {
            p->hand->addCardHand(deck->draw());
            p->recieve_card = false;
        }
        p->deployed_inTurn =new int(0);
        p->orders->order_list.clear();

    }
}
string GameEngine::reinforcementPhase() {
    for (int i = 1; i < all_players.size() + 1; i++) {
        Player* p = getPlayer(all_players,i);
        assignArmy(p);
    }


    std::list<Continent*>::iterator it;
    for (it = map->m_Continents.begin(); it != map->m_Continents.end(); ++it) {
        std::list<Territory*>::iterator it_ter;
        string owner_name = *(*it)->m_Territories.front()->player_owner;
        for (it_ter = (*it)->m_Territories.begin(); it_ter != (*it)->m_Territories.end(); ++it_ter) {

            if (owner_name != *(*it_ter)->player_owner) {
                owner_name = "";
                break;
            }

        }
        if (owner_name != "") {
            Player*  p = getPlayer(all_players, owner_name);
            *p->armies = *p->armies + *(*it)->control_val;
        }
    }
    return "";
}

void GameEngine::mainGameLoop() {
    current_state = getstate("assignreinforcement");

    while (true) {

        if (*current_state->name == "assignreinforcement") {
            endTurnPhase();
            string problem = reinforcementPhase();
            current_state = getstate("issueorders");
        }

        string message = "";
        cout << "current state is : " + *current_state->name << endl;
         currentCommand = Cp->getCommand();
         if (currentCommand->getCommand() == "nullptr")
             return;
        string com, arg;
        com = string(currentCommand->getCommand().substr(0, currentCommand->getCommand().find(" ")));

        arg = currentCommand->getCommand().substr(currentCommand->getCommand().find(" ") + 1);
  
            message = transitionInGame(com, arg);
            cout << message;
        
        if ((message) == "end") { return; }
    }
}
//the game loop
void GameEngine::manage()
{
    string message = "";
    while (true) {

        cout << "current state is : " + *current_state->name<<endl;
        cout << "possible actions are : " + listPossibilities() << endl;
         currentCommand = Cp->getCommand();

         if (currentCommand->getCommand() == "nullptr")
             return;
        string com, arg;
        com = string(currentCommand->getCommand().substr(0, currentCommand->getCommand().find(" ")));

        arg = currentCommand->getCommand().substr(currentCommand->getCommand().find(" ") + 1);
        if (!check_command(com)) {
            cout << "INVALID COMMAND \n";
        }
        else {
            message = transition(com, arg);
            cout << message;
        }
        if (*(current_state->name) == "gamestart"){return;}

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
    std::list<string*> command_list;

    std::list<State*> all_states;
    for (std::list<State*>::iterator it = all_states.begin(); it != all_states.end(); ++it) {
        delete *it;
        *it= nullptr;
    }
    
    for (std::list<string*>::iterator it = command_list.begin(); it != command_list.end(); ++it) {
        delete *it;
        *it= nullptr;
    }

        
}


//***********STATE *************

State::State(string name)
{
    this->name = new string(name);
    possible_action[3] = {}; // the potential transitions command it accepts
    possible_states[3] =  {};
}

State::State()
{
    name = new string();
     possible_action[3] = {}; // the potential transitions command it accepts
     possible_states[3] =  {}; // the potential states it eventually gets to

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
    
    for(int i=0; i< 3 ;i++){
        delete possible_states[i];
        possible_states[i]= nullptr;
        delete possible_action[i];
        possible_action[i]=nullptr;
    }
    
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

