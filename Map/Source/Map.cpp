#include "Map.h"
#include <iostream>


using namespace std;
Map::Map(string line)
{

	string Line = string(line.substr(0, line.find("\n") + 1));
	Line = Line.substr(0, line.find("=")+1 );
	m_author = new string(line.substr(Line.length()));
	


	line = line.substr(line.find("\n") + 1);// PARSE THE REST IF NEEDED


}


Continent* getContinent2(std::list<Continent*> Li, string name) {
    std::list<Continent*>::iterator it;
    for (it = Li.begin(); it != Li.end(); ++it) {
        if (name == *(*it)->m_name) {
            return (*it);
        }
    }
    return nullptr;
}

Territory* getTerritory2(std::list<Territory*> Li, string name) {
    std::list<Territory*>::iterator it;
    for (it = Li.begin(); it != Li.end(); ++it) {

        if (name == *(*it)->m_name) {
            return (*it);
        }
    }
    return nullptr;
}
Territory* GotoNext(Territory* ter, list<Territory*> Visited_ter) {
    std::list<Territory*>::iterator it;
    for (it = ter->m_Connections.begin(); it != ter->m_Connections.end(); ++it) {

        if (getTerritory2(Visited_ter, *(*it)->m_name) == nullptr ) {
            return (*it);
        }
    }
    return nullptr;
}

bool Map::Validate()
{
    std::list<Territory*>::iterator it;
    for (it = m_Territories.begin(); it != m_Territories.end(); ++it) {

        if ((*it)->m_Connections.size()==0) {
            return false;
        }
    }

    std::list<Continent*>::iterator itCont;
    
    for (itCont = m_Continents.begin(); itCont != m_Continents.end(); ++itCont) {
     
        if ((*itCont)->m_Connections.size() == 0) {
            return false;
        }
    }
 
     
    for (it = m_Territories.begin(); it != m_Territories.end(); ++it) {
        int count=0;
        for (itCont = m_Continents.begin(); itCont != m_Continents.end(); ++itCont) {

                if (getTerritory2((*itCont)->m_Territories, *(*it)->m_name) != nullptr) {
                    count +=1;

               }
              
            
        }
        if (count != 1) {
            cout << *(*it)->m_name << " has more than one or no continent "<<endl;
            return false;
        }
    }


	return true;
}

bool Map::addContinent(Continent Con)
{
	return false;
}



