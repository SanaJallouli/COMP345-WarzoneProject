
#include "MapLoader.h"

#include <iostream>

#include <fstream>



using namespace std;
MapLoader::MapLoader()
{
    m_map_desc = new string();
}

Continent* getContinent(std::list<Continent*> Li, string name) {
    std::list<Continent*>::iterator it;
    for (it = Li.begin(); it != Li.end(); ++it) {
        if (name == *(*it)->m_name) {
            return (*it);
        }
    }
    return nullptr;
}

Territory* getTerritory(std::list<Territory*> Li, string name) {
    std::list<Territory*>::iterator it;
    for (it = Li.begin(); it != Li.end(); ++it) {

        if (name == *(*it)->m_name) {
            return (*it);
        }
    }
    return nullptr;
}
void MapLoader::Print(std::list<Continent*> Li) {
    std::list<Continent*>::iterator it;
    for (it = Li.begin(); it != Li.end(); ++it) {
        cout << *(*it)->m_name<< " CONTAINS THESE : ";
        Print((*it)->m_Territories);
        cout << endl;
    }
  
}

void MapLoader::Print(std::list<Territory*> Li) {
    std::list<Territory*>::iterator it;
    std::list<Territory*>::iterator it2;
    for (it = Li.begin(); it != Li.end(); ++it) {
        cout << *(*it)->m_name<<endl<< "AND AM CONNECTED TO THESE ";
        cout << (*it)->m_Connections.size()<<endl;
      
    
    }
    cout << endl;

}




bool MapLoader::LoadMap()
{
    string description="";
    string map = m_map_desc->substr(m_map_desc->find("[Map]"), m_map_desc->find("[Continents]"));
    map= map.substr(6);
 
    
   m_map=new Map(map);



   



    description = m_map_desc->substr(m_map_desc->find("[Continents]"));
    string cont = description.substr(0, description.find("[Territories]"));
    cont = cont.substr(13);

    string contLine ="";

    while (cont != "") {
      
        
      
            contLine = cont.substr(0, cont.find("\n") + 1);
            if (contLine.find("=") != std::string::npos) {

                Continent* continent = new Continent(contLine);
                m_map->m_Continents.insert(m_map->m_Continents.begin(), continent);
            }
       
    cont = cont.substr(cont.find("\n") + 1);
   
    }
  
   


    
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




 while (TerritoryLink != "") {

     TerritoryLine = TerritoryLink.substr(0, TerritoryLink.find("\n") + 1);
     if (TerritoryLine.find(",") != std::string::npos) {

         
         Link( TerritoryLine);
     }
     TerritoryLink = TerritoryLink.substr(TerritoryLink.find("\n") + 1);

 }



 /// LOOOP AGAIN AND PROCESS EACH 

	return false;
}

bool MapLoader::Link(string line) {

    string terr_name = line.substr(0, line.find(","));
    line = line.substr(line.find(",") + 1);
    line = line.substr(line.find(",") + 1);
    line = line.substr(line.find(",") + 1);
   
    string contin = line.substr(0,line.find(",") );
    Territory* terri = getTerritory(m_map->m_Territories, terr_name);
    Continent* cont = getContinent(m_map->m_Continents, contin);

    if (cont == nullptr) {
        cout << contin << "  CONTINENT NOT FOUND BRO  ";
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
    return false;
 }




bool MapLoader::ReadDescription(std::string FilePath)
{
    string text = "";


    string Line;
    // open file in read mode
    ifstream input("1.txt");//will be modified 
    // Read line
 
    // until file is empty: print line, then read other line
    while (getline(input, Line)) {
       
        
        text += Line+"\n";
    }


    *m_map_desc = text;
   

   
	return false;
}

