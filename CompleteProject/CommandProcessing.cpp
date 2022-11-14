using namespace std;
#include <iostream>
#include <utility>
#include "string"
#include "CommandProcessing.h"


Command::Command() {

}


Command::Command(string s,LogObserver* l ) {
    command = s;
    lo = l;
    Attach(lo);
}
Command::~Command()
{
}
;

Command::Command(const Command& g) {
    command = g.command;
    effect = g.effect;

}

Command& Command::operator=(const Command& g)
{
    command = g.command;
    effect = g.effect;

    return     *this;;
}


void Command::setCommand(std::string command1) {
    command = command1;
}

void Command::setEffect(std::string effect1){

    effect = effect1;
    Notify(this);
}

string Command::getCommand(){
    return command;
}

string Command::getEffect(){
    return effect;
}

string Command::stringToLog()
{
    return "the command : <"+getCommand()+"> was set with the following effect <"+getEffect()+">";
}






//validate if the command can be done or not 

string CommandProcessor::stringToLog()
{
    return "this command : <"+commands_vector.back()->getCommand()+"> was saved to the command vector";
}

CommandProcessor::CommandProcessor(LogObserver* l) {   lo = l;
    possible_valid_commands_vector = { "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit" ,"deploy","advance","negotiate","bomb","airlift","issueorders","execorder","end"};
    valid_commands_and_their_transitions_vector.emplace_back("start", make_pair("loadmap", "maploaded"));
    valid_commands_and_their_transitions_vector.emplace_back("maploaded", make_pair("loadmap", "maploaded"));
    valid_commands_and_their_transitions_vector.emplace_back("maploaded", make_pair("validatemap", "mapvalidated"));
    valid_commands_and_their_transitions_vector.emplace_back("mapvalidated", make_pair("addplayer", "playersadded"));
    valid_commands_and_their_transitions_vector.emplace_back("playersadded", make_pair("addplayer", "playersadded"));
    valid_commands_and_their_transitions_vector.emplace_back("playersadded", make_pair("gamestart", "assignreinforcement"));
    valid_commands_and_their_transitions_vector.emplace_back("assignreinforcement", make_pair("issueorder", "issueorders"));
    valid_commands_and_their_transitions_vector.emplace_back("issueorders", make_pair("issueorder", "issueorders"));
    valid_commands_and_their_transitions_vector.emplace_back("issueorders", make_pair("endissueorders", "executeorders"));
    valid_commands_and_their_transitions_vector.emplace_back("executeorders", make_pair("execorder", "executeorders"));
    valid_commands_and_their_transitions_vector.emplace_back("executeorders", make_pair("endexecorders", "assignreinforcement"));
    valid_commands_and_their_transitions_vector.emplace_back("executeorders", make_pair("win", "win"));
    valid_commands_and_their_transitions_vector.emplace_back("win", make_pair("replay", "start"));
    valid_commands_and_their_transitions_vector.emplace_back("win", make_pair("quit", "exit program"));
    Attach(l);
}

void CommandProcessor::readCommand() {
    
    string temp_str;
    cout << "Please enter commands one after the other. When you are finished please enter in all caps \"END\"" << endl;
    while(true){
 
        std::getline(std::cin, temp_str);

        if(temp_str=="END"){
            break;
        }
        string com = string(temp_str.substr(0, temp_str.find(" ")));
        if (find(possible_valid_commands_vector.begin(), possible_valid_commands_vector.end(), com) != possible_valid_commands_vector.end()){
            saveCommand(temp_str);
            cout << "Valid command. Successfully entered." << endl;
        }
        else {
            cout << "The command that you entered was an invalid command. Please enter another command or type \"END\" once finished." << endl;
        }
    }


}



Command* CommandProcessor::getCommand(){
  
    if (index == commands_vector.size()) {
        readCommand();
    }
    index++;
    if (index > commands_vector.size())
        exit(0);
    std::cout << commands_vector[index - 1]->getCommand() << endl;
    return commands_vector[index-1];

}

std::string CommandProcessor::validate(Command* command1, std::string state )
{
    std::vector<pair<string, string>> value_vector;
    for (auto it = valid_commands_and_their_transitions_vector.begin(); it != valid_commands_and_their_transitions_vector.end(); ++it) {
        if (it->first == state) {
            value_vector.emplace_back(it->second);
        }
    }
    for (auto it = value_vector.begin(); it != value_vector.end(); ++it) {
        if (it->first == command1->getCommand()) {
            cout << "Command " << command1 << " has been validated.\nState has been changed to " << it->second << endl;
            state = it->second;
            //ALSO NEED TO SAVE EFFECT HERE
            return state;
        }
        else {
            cout << "Command" << command1 << " could not be validated, state has not changed" << endl;
            return state;
        }
    }
    cout << "ERROR\nThe command could not be validated. State has not changed. Please try again with a different command" << endl;
    return state;
}

void CommandProcessor::saveCommand(string c) {
    
    commands_vector.insert(commands_vector.end(), new Command(c,lo));
    Notify(this);
}


FileLineReader::FileLineReader()
{

}

void FileLineReader::readAllFile(string filename,LogObserver* l) {
    std::vector<Command*> local_commands_vector;
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        
        commands.insert(commands.end(), new Command(line,l));
    }
}

Command* FileLineReader::getNextCommand(string filename, LogObserver* l)
{
    if (index == 0) { 
        readAllFile(filename,l );
    }
    index++;
    if (index == commands.size()) {
        cout << "There are no more commands to play the program will exit" << endl;
        exit(1);
        return nullptr;
    }
    return commands[index - 1];
}


CommandProcessorAdapter::CommandProcessorAdapter(FileLineReader* f,string fl,LogObserver* l):CommandProcessor(l) {
    Fl = f;
    filename = fl;
}
void CommandProcessorAdapter::readCommand()
{
    string temp_str= (*Fl).getNextCommand(filename,lo)->getCommand();
    string com = string(temp_str.substr(0, temp_str.find(" ")));
    if (find(possible_valid_commands_vector.begin(), possible_valid_commands_vector.end(), com) != possible_valid_commands_vector.end()) {
        saveCommand(temp_str);
        cout << "Valid command. Successfully entered." << endl;
    }
    else {
        cout << "The command that you entered was an invalid command. Please enter another command or type \"END\" once finished." << endl;
    } 
}




