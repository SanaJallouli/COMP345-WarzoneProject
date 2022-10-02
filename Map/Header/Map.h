#pragma once

#include <list>

#include "Continent.h"
using namespace std;
class Map
{
	


public:
	list<Continent*> m_Continents; // list of all the continents
	std::list<Territory*> m_Territories;
	string* m_author;

	Map(string author);

	bool Validate();

	bool addContinent(Continent Con);

		


};