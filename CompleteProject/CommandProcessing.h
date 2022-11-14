

#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include "LoggingObserver.h"
class Command: public ILoggable , public Subject {
private:
    std::string command;
    std::string effect;
public:
    void setCommand(std::string);
    void setEffect(std::string effect1);
    std::string getCommand();
    std::string getEffect();
    string logging;
    string stringToLog() override;
    LogObserver* lo;

    Command();
    Command(string s,LogObserver* l);
    ~Command();
    Command(const Command& g);
    Command& operator=(const Command& g);
};


class CommandProcessor :public  ILoggable, public Subject {

public:
    bool ReadFromFile = false;
   virtual void readCommand();
   LogObserver* lo;
    std::vector<std::pair<std::string, std::pair<std::string, std::string>>> valid_commands_and_their_transitions_vector;
    std::vector<std::string> possible_valid_commands_vector;
    std::vector<Command*> commands_vector;
    string stringToLog() override;
    int index = 0;
    CommandProcessor(LogObserver* lo);
    Command* getCommand();
    std::string validate(Command*, std::string);
    CommandProcessor();
    void saveCommand(string c);
};




class FileLineReader {

public:
    FileLineReader();
    std::vector<Command*> commands;
    void readAllFile(string filename,  LogObserver* l);
    int index = 0;
    Command* getNextCommand(string filename, LogObserver* l);
};

class CommandProcessorAdapter : public  CommandProcessor {
public:
    FileLineReader* Fl;
    string filename;
    CommandProcessorAdapter();
    CommandProcessorAdapter(FileLineReader* f,string fl,LogObserver* l);
    void readCommand() override;

};




#endif




