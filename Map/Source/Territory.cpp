#include "Territory.h"
#include <iostream>











using namespace std;

Territory::Territory(std::string name, int num1, int m_num2, std::string continents)
{
}

Territory::Territory(std::string line)
{
	m_name = new string(line.substr(0, line.find(",")  ));
	
	line = line.substr( line.find(",") + 1);

	m_x = new string(line.substr(0, line.find(",") ));
	line = line.substr(line.find(",") + 1);
	
	m_y = new string(line.substr(0, line.find(",") ));
	line = line.substr(line.find(",") + 1);
	
	m_continent_name = new string(line.substr(0, line.find(",") ));

	line = line.substr(line.find(",") + 1);

}
Territory* getTerritory3(std::list<Territory*> Li, string name) {
	std::list<Territory*>::iterator it;
	for (it = Li.begin(); it != Li.end(); ++it) {
		if (name == *(*it)->m_name) {
			return (*it);
		}
	}
	return nullptr;
}

bool Territory::AddConnection(Territory* ter)
{
	if (getTerritory3(m_Connections, *ter->m_name) == nullptr) {
		m_Connections.insert(m_Connections.begin(), ter);
	}
	return false;
}


