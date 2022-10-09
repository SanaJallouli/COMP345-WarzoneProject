#include "Map_driver.h"
#include "CardsDriver.h"
#include <string>
#include <iostream>


int main(){

	//map part 1
	std::cout << std::endl 
		<< " ===== testLoadMaps() start ===== " << std::endl;
	//testLoadMaps();
	std::cout << std::endl
		<< " ===== testLoadMaps() end ===== " << std::endl;

	//card part 4
	testCards(); 

	//pause the console
	std::cout << std::endl << "Press any key and enter to exit: ";
	std::string input;
	std::cin >> input;

	return 0;
}
