#include "Continent.h"
#include <iostream>







using namespace std;
Continent::Continent(string line)
{
	string Line = string(line.substr(0, line.find("\n") + 1));
	m_name =new string(Line.substr(0, line.find("=") ));

}

bool Continent::addTerritory(Territory* ter)
{
	m_Territories.insert(m_Territories.begin(), ter);
	return false;
}
Continent* getContinent3(std::list<Continent*> Li, string name) {
	std::list<Continent*>::iterator it;
	for (it = Li.begin(); it != Li.end(); ++it) {
		if (name == *(*it)->m_name) {
			return (*it);
		}
	}
	return nullptr;
}

bool Continent::AddConnection(Continent* con)
{
	if (getContinent3(m_Connections, *con->m_name) == nullptr) {
		m_Connections.insert(m_Connections.begin(), con);
	}
	return false;
	return false;
}


