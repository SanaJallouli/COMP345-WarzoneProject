//#include "Territory.h"
//#include <iostream>
//#include "Utility_map.h"
//
//using namespace std;
//
//Territory::~Territory() // destructor
//{ 
//	delete m_continent_name;
//	m_continent_name = nullptr;
//	delete m_name;
//	m_name = nullptr;
//	delete m_x;
//	m_x = nullptr;
//	delete m_y;
//	m_y = nullptr;
//}
//
//Territory::Territory(const Territory& ter) // copy constructor 
//{
//	this->m_continent_name =  new string(*ter.m_continent_name);
//	this->m_name =  new string(*ter.m_name);
//	this->m_x = new string(*ter.m_x);
//	this->m_y = new string(*ter.m_y);
//	this->m_Connections =  list<Territory*>(ter.m_Connections);
//}
//
//Territory& Territory::operator=(const Territory& ter) // assign operator 
//{
//	this->m_continent_name = new string(*ter.m_continent_name);
//	this->m_name = new string(*ter.m_name);
//	this->m_x = new string(*ter.m_x);
//	this->m_y = new string(*ter.m_y);
//	this->m_Connections = list<Territory*>(ter.m_Connections);
//	return *this;
//}
//
//
//Territory::Territory(std::string line) // create a territory from a line in the territory section
//{
//	m_name = new string(line.substr(0, line.find(",")  ));
//	
//	line = line.substr( line.find(",") + 1);
//
//	m_x = new string(line.substr(0, line.find(",") ));
//	line = line.substr(line.find(",") + 1);
//	
//	m_y = new string(line.substr(0, line.find(",") ));
//	line = line.substr(line.find(",") + 1);
//	
//	m_continent_name = new string(line.substr(0, line.find(",") ));
//
//	line = line.substr(line.find(",") + 1);
//
//}
//
//
//bool Territory::AddConnection(Territory* ter) 
//{
//	if (getTerritory(m_Connections, *ter->m_name) == nullptr) {
//		m_Connections.insert(m_Connections.begin(), ter);
//	}
//	return false;
//}
//
//ostream& operator<<(ostream& strm, const Territory& cont) // cout operator 
//{
//	string str = "";
//
//	for (list<Territory*>::const_iterator it = (cont.m_Connections).begin(); it != cont.m_Connections.end(); ++it) {
//		str += *(*it)->m_name + " , ";
//	}
//
//	return strm << "Name OF THE territory  : " << *(cont.m_name) << endl
//		<< "Xposition   : " << *(cont.m_x) << endl << "   Yposition   : " << *(cont.m_y) << endl
//		<< "Part of the  Continent  : " << *(cont.m_continent_name) << endl <<
//
//		" Connected terrytories :  " << str << endl;
//};
//
