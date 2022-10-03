#pragma once 
#include "Map.h"
#include <iostream>
#include "Utility_map.h"


using namespace std;
Map::Map(string line) // creating map from the map section in the file 
{

	string Line = string(line.substr(0, line.find("\n") + 1));
	Line = Line.substr(0, line.find("=")+1 );
	m_author = new string(line.substr(Line.length()));
	


	line = line.substr(line.find("\n") + 1);// PARSE THE REST IF NEEDED


}
Map::~Map() // destructor 
{

    delete m_author;
    m_author = nullptr;

}



bool Map::Validate() 
{

    // going through the territories and checking that all of them have at least one connection  to check for a connected graph 
    std::list<Territory*>::iterator it;
    for (it = m_Territories.begin(); it != m_Territories.end(); ++it) {

        if ((*it)->m_Connections.size()==0) {
            return false;
        }
    }

    std::list<Continent*>::iterator itCont;
    // going through the continents and checking that all of them have at least one connection  to check for a connected graph and have at least one memeber 
    for (itCont = m_Continents.begin(); itCont != m_Continents.end(); ++itCont) {
     
        if ((*itCont)->m_Connections.size() == 0) {
            return false;
        }
        if ((*itCont)->m_Territories.size() == 0) {
            return false;
        }
    }
 
    // going through the territories and checking that all of them are part of one continent each

    for (it = m_Territories.begin(); it != m_Territories.end(); ++it) {
        int count=0;
        for (itCont = m_Continents.begin(); itCont != m_Continents.end(); ++itCont) {

                if (getTerritory((*itCont)->m_Territories, *(*it)->m_name) != nullptr) {
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

Map& Map::operator=(const Map& map) { // assign operator 
    m_author = new string(*map.m_author);
    m_Territories = list<Territory*>(map.m_Territories);
    m_Continents = list<Continent*>(map.m_Continents);
    return *this;
}


Map::Map(const Map& map) { // copy constructor 
    m_author = new string(*map.m_author);
    m_Territories = list<Territory*>(map.m_Territories);
    m_Continents = list<Continent*>(map.m_Continents);
}


ostream& operator<<(ostream& strm,  const Map& map) // cout operator
{
    string str="";
    string strcont="";


    for (list<Continent*>::const_iterator itcont = (map.m_Continents).begin(); itcont != map.m_Continents.end(); ++itcont) {
        strcont += *(*itcont)->m_name + " , ";
    }
    for (list<Territory*>::const_iterator  it = (map.m_Territories).begin()  ; it != map.m_Territories.end(); ++it) {
        str += *(*it)->m_name+" , ";
    }
    return strm << "Author : " << *(map.m_author) << endl << " My Continents :  " << strcont << endl<< endl<< " My terrytories "<< str<<endl;
};

