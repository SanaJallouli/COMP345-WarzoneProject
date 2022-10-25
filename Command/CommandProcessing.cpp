using namespace std;
#include <iostream>
#include <utility>
#include "string"
#include "CommandProcessing.h"

Command::Command(std::string the_command) {
    setCommand(the_command);
};

void Command::setCommand(std::string command1) {
    this->command = command1;
}

void Command::setEffect(std::string effect1){
    this->effect = effect1;
}

string Command::getCommand(){
    return this->command;
}

string Command::getEffect(){
    return this->effect;
}






//validate if the command can be done or not 

CommandProcessor::CommandProcessor(){
    possible_valid_commands_vector = {"loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit"};
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

vector<Command*> CommandProcessor::readCommand() {
    vector<Command*> local_commands_vector;
    string temp_str;
    cout << "Please enter commands one after the other. When you are finished please enter in all caps \"END\"" << endl;
    while(true){
        cin >> temp_str;
        if(temp_str=="END"){
            break;
        }
        if (find(possible_valid_commands_vector.begin(), possible_valid_commands_vector.end(), temp_str) != possible_valid_commands_vector.end()){
            local_commands_vector.emplace_back(new Command(temp_str));
            cout << "Valid command. Successfully entered." << endl;
        }
        else {
            cout << "The command that you entered was an invalid command. Please enter another command or type \"END\" once finished." << endl;
        }
    }
    return local_commands_vector;
}

void CommandProcessor::getCommand(string filename) {
    //read from console
  
    if (filename.empty()){
        vector<Command*> local_commands_pointer_vector = readCommand();
        saveCommand(local_commands_pointer_vector);
        cout << "All entered commands successfully saved";
    }
        //read from filename
  
    else{
        auto* adapter = new FileCommandProcessorAdapter();
        vector<Command*> local_commands_pointer_vector = adapter->readCommand(filename);
        saveCommand(local_commands_pointer_vector);
        cout << "Finished with " << filename << endl;
    }
}

void CommandProcessor::saveCommand(vector<Command *> local_commands_vector){
    for (Command *command: local_commands_vector){
        commands_vector.emplace_back(command);
        cout << "Saved " << command->getCommandString() << std::endl;
    }
}

//returns state that it transitions to given current state and command that was entered (if it transitions to a different state)
string CommandProcessor::validate(Command* command1, string state) {
    std::vector<pair<string, string>> value_vector;
    for(auto it = valid_commands_and_their_transitions_vector.begin(); it != valid_commands_and_their_transitions_vector.end(); ++it){
        if(it->first==state){
            value_vector.emplace_back(it->second);
        }
    }
    for(auto it = value_vector.begin(); it != value_vector.end(); ++it){
        if(it->first==command1->getCommandString()){
            cout << "Command " << command1 << " has been validated.\nState has been changed to "<< it->second << endl;
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


std::vector<Command*> FileCommandProcessorAdapter::readCommand(std::string filename) {
    std::vector<Command*> final_commands;
    possible_valid_commands_vector = {"loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit"};
    std::vector<std::string> potential_commands = flr.readLineFromFile(filename);

    //validating that the commands are correct before returning them to the CommandProcessor, otherwise, skipping the item
  
    for(std::string str: potential_commands){
        if (find(possible_valid_commands_vector.begin(), possible_valid_commands_vector.end(), str) != possible_valid_commands_vector.end()){
            final_commands.emplace_back(new Command(str));
            std::cout << "Command \"" << str << "\" was valid. It has been successfully entered." << std::endl;
        }
        else{
            std::cout << "Command \"" << str << "\" was not valid. It will be skipped" << std::endl;
        }
    }
    return final_commands;
}



std::vector<std::string> FileLineReader::readLineFromFile(const std::string& filename) {
    std::vector<std::string> local_commands_vector;
    std::ifstream infile(filename);
    std::string line;
    while(std::getline(infile, line)){
        local_commands_vector.emplace_back(line);
    }
    return local_commands_vector;
}
