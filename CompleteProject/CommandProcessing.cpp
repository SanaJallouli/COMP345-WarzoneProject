using namespace std;
#include <iostream>
#include <utility>
#include "string"
#include "CommandProcessing.h"


Command::Command() {

}
Command::Command(string s) {
    command = s;
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

    // TODO: insert return statement here
    return     *this;;
}


void Command::setCommand(std::string command1) {
    command = command1;
}

void Command::setEffect(std::string effect1){
    effect = effect1;
}

string Command::getCommand(){
    return command;
}

string Command::getEffect(){
    return effect;
}






//validate if the command can be done or not 

CommandProcessor::CommandProcessor(){
    possible_valid_commands_vector = { "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit" };
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

}

void CommandProcessor::readCommand() {
    /*
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
    }*/
    FileLineReader f=FileLineReader();
    this->commands_vector = f.readLineFromFile("C:\\Users\\bechr\\Documents\\GitHub\\COMP345-WarzoneProject\\all\\working\\1.txt");

}



Command CommandProcessor::getCommand(){
  
    if (index == commands_vector.size()) {
        readCommand();
    }
    index++;
    if (index > commands_vector.size())
        exit(0);
    return *commands_vector[index-1];

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
    commands_vector.insert(commands_vector.end(), new Command(c));
}







/*

std::vector<Command*> FileCommandProcessorAdapter::readCommand(std::string filename) {
    std::vector<Command*> final_commands;
    possible_valid_commands_vector = {"loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit"};
    std::vector<std::string> potential_commands = readLineFromFile(filename);

    //validating that the commands are correct before returning them to the CommandProcessor, otherwise, skipping the item
  
    for(std::string str: potential_commands){
        if (find(possible_valid_commands_vector.begin(), possible_valid_commands_vector.end(), str) != possible_valid_commands_vector.end()){
            final_commands.insert(final_commands.end(),new Command(str));
            std::cout << "Command \"" << str << "\" was valid. It has been successfully entered." << std::endl;
        }
        else{
            std::cout << "Command \"" << str << "\" was not valid. It will be skipped" << std::endl;
        }
    }
    return final_commands;
}

*/

std::vector<Command*> FileLineReader::readLineFromFile(const std::string& filename) {
    std::vector<Command*> local_commands_vector;
    std::ifstream infile(filename);
    std::string line;
    while(std::getline(infile, line)){

        local_commands_vector.insert(local_commands_vector.end(), new Command(line));
    }
 
    return local_commands_vector;
}
