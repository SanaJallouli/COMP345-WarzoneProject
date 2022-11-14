

#include "CommandProcessingDriver.h"

void CommandProcessorDriver() {
    bool fromfile = true;

        cout << "******************** TestCommandProcessor fromfile ******************* \n" << endl;
        GameEngine* ge = new GameEngine(fromfile);
        ge->StartupPhase();
        ge->mainGameLoop();

        cout << "******************** TestCommandProcessor from command line ******************* \n" << endl;

       ge = new GameEngine(!fromfile);
        ge->StartupPhase();
        ge->mainGameLoop();
        return;
}