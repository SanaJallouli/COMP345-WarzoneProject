#pragma once
#include <vector>
#include <string>

#include <ostream>
#include <list>
using namespace std;
class Territory 
{



public:
	string* m_name;
	string* m_x;
	string* m_y;
	string* m_continent_name;
	list<Territory*> m_Connections; // store the continent it is connected to 
	
	Territory(std::string name , int num1 ,int m_num2, std::string continents);
	Territory(std::string line);
	bool AddConnection(Territory* ter);

};