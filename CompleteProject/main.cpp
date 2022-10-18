#include <iostream>
#include "GameEngineDriver.hpp"
#include "MapDriver.hpp"
#include "OrderDriver.hpp"
#include "PlayerDriver.hpp"
#include "CardsDriver.hpp"

int main(int argc, const char * argv[]) {
    testLoadMaps();
    testPlayers();
    testOrdersList();
    testCards();
    testGameStates();
}
