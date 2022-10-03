#pragma once 
#include "MapLoader.h"
#include "Utility_map.h"

#include <iostream>

#include <fstream>



using namespace std;


ostream& operator<<(ostream& strm, const MapLoader& map) // cout operator 
{
    string desc;
    string intializedmap;
    if (map.m_map_desc != nullptr)
        desc = *map.m_map_desc;
    else
        return strm << " The description of the map has not been defined yet  " << endl;

    if (map.m_map != nullptr)
        intializedmap = "and the map has been initialized ";
    else
        return strm << " This is the description already read however the map has not been initialized \n here is the description \n" << desc << endl;
    return strm << " This is the description already read and the map was initialized  \n here is the description \n" << desc << endl;

    // TODO: insert return statement here
}

MapLoader& MapLoader::operator=(const MapLoader& map) { // assign operator 
    this->m_map_desc = new string(*map.m_map_desc);
    this->m_map = new Map(*map.m_map);
    return *this;
}


MapLoader::MapLoader(const MapLoader& map) { // copy contructor 
    this->m_map_desc = new string(*map.m_map_desc);
    this->m_map = new Map(*map.m_map);
}

MapLoader::MapLoader() //default constructor 
{
    m_map_desc = new string();
}

MapLoader::~MapLoader()// destructor 
{
    delete m_map;
    m_map = nullptr; // avoiding dangling pointer 
   delete m_map_desc;
   m_map_desc = nullptr;
}

// extra visual helper methods 
void MapLoader::Print(std::list<Continent*> Li) { // printing a list of continents 
    std::list<Continent*>::iterator it;
    for (it = Li.begin(); it != Li.end(); ++it) {
        cout << *(*it)->m_name<< " CONTAINS THESE : ";
        Print((*it)->m_Territories);
        cout << endl;
    }
  
}

void MapLoader::Print(std::list<Territory*> Li) { // printing a list of territories 
    std::list<Territory*>::iterator it;
    std::list<Territory*>::iterator it2;
    for (it = Li.begin(); it != Li.end(); ++it) {
        cout << *(*it)->m_name<<endl<< "AND AM CONNECTED TO THESE ";
        cout << (*it)->m_Connections.size()<<endl;
      
    
    }
    cout << endl;

}




void  MapLoader::LoadMap()
{
    string description="";
    string map = m_map_desc->substr(m_map_desc->find("[Map]"), m_map_desc->find("[Continents]"));
    map= map.substr(6);
    //reading the map description
   m_map=new Map(map);
    description = m_map_desc->substr(m_map_desc->find("[Continents]"));
    string cont = description.substr(0, description.find("[Territories]"));
    cont = cont.substr(13);

    string contLine ="";
    // reading the continent description 
    while (cont != "") {
            contLine = cont.substr(0, cont.find("\n") + 1);
            if (contLine.find("=") != std::string::npos) {
                Continent* continent = new Continent(contLine);
                m_map->m_Continents.insert(m_map->m_Continents.begin(), continent);
            }
    cont = cont.substr(cont.find("\n") + 1);
   
    }
  
     
    // reading the territories one by one and creating a territory for each line 
        string TerritoryLine="emptyline";
 string Territories= m_map_desc->substr(m_map_desc->find("[Territories]")+14);
 string TerritoryLink = Territories;

 while (Territories != "") {

     TerritoryLine = Territories.substr(0, Territories.find("\n") + 1);
     if (TerritoryLine.find(",") != std::string::npos) {

         Territory* ter =new  Territory(TerritoryLine);
         m_map->m_Territories.insert(m_map->m_Territories.begin(), ter);
     }
     Territories = Territories.substr(Territories.find("\n") + 1);
     
 }
 // linking all the territories and putting them in respective continent 
 while (TerritoryLink != "") {

     TerritoryLine = TerritoryLink.substr(0, TerritoryLink.find("\n") + 1);
     if (TerritoryLine.find(",") != std::string::npos) {

         
         Link( TerritoryLine);
     }
     TerritoryLink = TerritoryLink.substr(TerritoryLink.find("\n") + 1);

 }




}
// link each territory and add it to its continent
void  MapLoader::Link(string line) {

    string terr_name = line.substr(0, line.find(","));
    line = line.substr(line.find(",") + 1);
    line = line.substr(line.find(",") + 1);
    line = line.substr(line.find(",") + 1);
   
    string contin = line.substr(0,line.find(",") );
    Territory* terri = getTerritory(m_map->m_Territories, terr_name);
    Continent* cont = getContinent(m_map->m_Continents, contin);

    if (cont == nullptr) { 
        cout << contin << " : CONTINENT NOT FOUND   ";
        exit(0);
    }
    cont->addTerritory(terri);
    line = line.substr(line.find(",") + 1)+",";

    string name = "initial";

    while (line != "") {
        name = line.substr(0, line.find(",") );
        name = name.substr(0, name.find("\n") );
        
        Territory* addTerri = getTerritory(m_map->m_Territories, name);
        if (addTerri == nullptr) {
            cout << name << "TERRITORY NOT FOUND BRO";
            exit(0);
        }
        terri->AddConnection(addTerri);
       
        if (*addTerri->m_continent_name != *terri->m_continent_name) {
            Continent* addCont = getContinent(m_map->m_Continents, *addTerri->m_continent_name);
            cont->AddConnection(addCont);
        }
        
        line = line.substr(line.find(",") + 1);

    }

 }



// reading the file and putting it all in a string 
void MapLoader::ReadDescription(std::string FilePath)
{
    string text = "";


    string Line;
    // open file in read mode
    ifstream input(FilePath);
    // Read line
 
    // until file is empty: print line, then read other line
    while (getline(input, Line)) {
       
        
        text += Line+"\n";
    }

    if (text.find("[Continents]") == std::string::npos) {
        cout << "The file does not contain section continent ";
        exit(0);
    }    if (text.find("[Territories]") == std::string::npos) {
        cout << "The file does not contain section Territories ";
        exit(0);
    }    if (text.find("[Map]") == std::string::npos) {
        cout << "The file does not contain section Map ";
        exit(0);
    }
    *m_map_desc = text;
   
    input.close();
   

}


