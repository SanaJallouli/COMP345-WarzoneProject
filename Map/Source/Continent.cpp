//#pragma once 
//#include "Continent.h"
//#include <iostream>
//#include "Utility_map.h"
//
//
//
//
//
//using namespace std;
//
//Continent::~Continent() // destructor 
//{
//
//	delete m_name;
//	m_name = nullptr;
//}
//Continent::Continent(string line) // constructor using the line in the file 
//{
//	string Line = string(line.substr(0, line.find("\n") + 1));
//	m_name =new string(Line.substr(0, line.find("=") ));
//
//}
//
//bool Continent::addTerritory(Territory* ter) 
//{
//	m_Territories.insert(m_Territories.begin(), ter);
//	return false;
//}
//
//
//bool Continent::AddConnection(Continent* con)
//{
//	if (getContinent(m_Connections, *con->m_name) == nullptr) {
//		m_Connections.insert(m_Connections.begin(), con);
//	}
//	return false;
//	return false;
//}
//
//Continent::Continent(const Continent& ter) // copy constructor 
//{
//	this->m_name = new string(*ter.m_name);
//	this->m_Territories = list<Territory*>(ter.m_Territories);
//	this->m_Connections = list<Continent*>(ter.m_Connections);
//
//}
//
//Continent& Continent::operator=(const Continent& ter) // assign operator 
//{
//	
//	this->m_name = new string(*ter.m_name);
//	
//	this->m_Territories = list<Territory*>(ter.m_Territories);
//	this->m_Connections = list<Continent*>(ter.m_Connections);
//	return *this;
//}
//
//
//ostream& operator<<(ostream& strm, const Continent& cont) // cout operator 
//{
//	string str = "";
//	string strcont = "";
//
//
//	for (list<Continent*>::const_iterator itcont = (cont.m_Connections).begin(); itcont != cont.m_Connections.end(); ++itcont) {
//		strcont += *(*itcont)->m_name + " , ";
//	}
//	for (list<Territory*>::const_iterator it = (cont.m_Territories).begin(); it != cont.m_Territories.end(); ++it) {
//		str += *(*it)->m_name + " , ";
//	}
//
//	return strm << "Name OF THE CONTINENT  : " << *(cont.m_name) << endl << " My terrytories :  " << strcont << endl << endl << " Connected to these Continents  :  " << str << endl;
//};