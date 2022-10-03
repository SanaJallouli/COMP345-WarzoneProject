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

	~Map();

	friend ostream& operator<<(ostream& strm, const Map& map);

	Map(const Map& ter);
	Map& operator=(const Map& map);



};