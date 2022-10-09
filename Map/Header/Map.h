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
	~Territory();
	Territory(const Territory& ter);
	Territory& operator=(const Territory& ter);
	Territory(std::string line);
	bool AddConnection(Territory* ter);
	friend ostream& operator<<(ostream& strm, const Territory& cont);
};


class Continent
{
public:
	string* m_name;
	std::list<Territory*> m_Territories; // store all territories in this continent 
	std::list<Continent*> m_Connections; // store the continent it is connected to 

	Continent(string line);
	~Continent();
	bool addTerritory(Territory* ter);

	bool AddConnection(Continent* con);
	friend ostream& operator<<(ostream& strm, const Continent& cont);
	Continent(const Continent& ter);
	Continent& operator=(const Continent& ter);
};

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


class MapLoader
{
public:
	MapLoader();
	~MapLoader();

	void Print(std::list<Continent*> Li);
	void Print(std::list<Territory*> Li);
	std::string* m_map_desc;
	Map* m_map;
	void LoadMap();
	void Link(string Line);
	void ReadDescription(std::string FilePath);
	MapLoader& operator=(const MapLoader& map);
	MapLoader(const MapLoader& map);
	friend ostream& operator<<(ostream& strm, const MapLoader& map);
};

Continent* getContinent(std::list<Continent*> Li, string name);
Territory* getTerritory(std::list<Territory*> Li, string name);