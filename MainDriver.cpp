#include "Map.h"
#include "GameEngine.h"
#include "Orders.h"
#include "Cards.h"
#include <string>
#include <iostream>


int main(){

	//part 1: map
	std::cout << std::endl 
		<< " ===== testLoadMaps() start ===== " << std::endl;
	//testLoadMaps();
	std::cout << std::endl
		<< " ===== testLoadMaps() end ===== " << std::endl;

	//part 2: player

	//part 3: order
	testOrdersList();

	//card part 4
	testCards(); 

	//part 5: game engine
	testGameStates();

	//pause the console
	std::cout << std::endl << "Press any key then enter to exit: ";
	std::string input;
	std::cin >> input;

	return 0;
}
