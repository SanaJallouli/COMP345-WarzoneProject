#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H


#include <string>
#include <fstream>
#include <vector>

class Command {
private:
    std::string command;
    std::string effect;
public:
    void setCommand(std::string);
    void setEffect(std::string effect1);
    std::string getCommand();
    std::string getEffect();
};


class CommandProcessor {
private:
    std::vector<std::pair<std::string, std::pair<std::string, std::string>>> valid_commands_and_their_transitions_vector;
    std::vector<std::string> possible_valid_commands_vector;
    std::vector<Command*> commands_vector;
    std::vector<Command*> readCommand();
public:
    CommandProcessor();
    void getCommand(std::string)
    std::string validate(Command*, std::string);
    void saveCommand(std::vector<Command*>);
};

class FileLineReader {
public:
    static std::vector<std::string> readLineFromFile(const std::string& file_name);
};

class FileCommandProcessorAdapter {
private:
    FileLineReader flr;
    std::vector<std::string> possible_valid_commands_vector;
public:
    std::vector<Command*> readCommand(std::string);
};





#endif
