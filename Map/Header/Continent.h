#pragma once
#include <list>

#include "Territory.h"
class Continent
{
	

public:
	string* m_name;
	std::list<Territory*> m_Territories; // store all territories in this continent 
	std::list<Continent*> m_Connections; // store the continent it is connected to 
	
	Continent(string line);
	bool addTerritory(Territory* ter);

	bool AddConnection(Continent* con);

};