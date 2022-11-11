#include "CommandProcessingDriver.h"


void testCommandProcessor(){
  cout<< "TEST COMMAND PROCESSOR. \n"<<endl;
  
    // Creating the CommandProcessor and (possibly unused) FileCommandProcessorAdapter
    CommandProcessor *cp;
    FileCommandProcessorAdapter *fcpa;

    cout << "Read commands from console or file?" << endl;

    string word1, word2;
    cin >> word1;

    // Catching wrong inputs
    while (word1 != "console" && word1 != "file") {
        cout << "Please try again!" << endl;
        cin >> word1;
    }

    // Creating a new CommandProcessor if reading from the console
    if (word1 == "console") {
        CommandProcessor *temp = new CommandProcessor;
        cp = temp;

        cout << "Please give a command: " << endl;
    }
    // Creating a new FileCommandProcessorAdapter if reading from a file
    else {
        cout << "Please provide the file name to read from:" << endl;
        cin >> word2;

        bool isValid = false;

        // Catching wrong inputs
        while (!isValid) {
            ifstream input(word2);

            if (input.is_open()) {
                isValid = true;
            } else {
                cout << "Please try again!" << endl;
                cin >> word2;
            }
        }

        fcpa = new FileCommandProcessorAdapter(word2);
        cp = fcpa;
    }
  
  
};
