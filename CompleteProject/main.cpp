#include <iostream>
#include "GameEngineDriver.hpp"
#include "MapDriver.hpp"
#include "OrderDriver.hpp"
#include "PlayerDriver.hpp"
#include "CardsDriver.hpp"
#include "CommandProcessing.h"
#include "CommandProcessingDriver.h"
#include "OrderDriver.hpp"

int main(int argc, const char * argv[]) {
    TestDeploy();
    TestAdvance();
    TestNegociate();
    TestBlockade();
   CommandProcessorDriver();
    testGameStates();
}
