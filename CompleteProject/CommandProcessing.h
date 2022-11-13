

#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H
#include <string>
#include <fstream>
#include <vector>
#include <list>

class Command {
private:
    std::string command;
    std::string effect;
public:
    void setCommand(std::string);
    void setEffect(std::string effect1);
    std::string getCommand();
    std::string getEffect();

    Command();
    Command(string s);
    ~Command();
    Command(const Command& g);
    Command& operator=(const Command& g);
};


class CommandProcessor {
private:
  
    bool ReadFromFile = false;
    void readCommand();
public:
    std::vector<std::pair<std::string, std::pair<std::string, std::string>>> valid_commands_and_their_transitions_vector;
    std::vector<std::string> possible_valid_commands_vector;
    std::vector<Command*> commands_vector;

    int index = 0;
    CommandProcessor();
    Command getCommand();
    std::string validate(Command*, std::string);
    void saveCommand(string c);
};









class FileLineReader {
public:
    std::vector<Command*> readLineFromFile(const std::string& file_name);
};

class FileCommandProcessorAdapter {
private:
    FileLineReader flr;
    std::vector<std::string> possible_valid_commands_vector;
public:
    std::vector<Command*> readCommand(std::string);
};
#endif




