#pragma once
#include "Map.h"

#include <list>
class MapLoader
{


public:
	MapLoader();
	void Print(std::list<Continent*> Li);
	void Print(std::list<Territory*> Li);
	std::string* m_map_desc;
	Map* m_map;
	 bool LoadMap();
	 bool Link(string Line);
	 bool ReadDescription(std::string FilePath);
	 std::list<Territory*> m_Territories; // store all territories in this continent 
	 std::list<Continent*> m_Continents; // store the continent it is connected to 
};