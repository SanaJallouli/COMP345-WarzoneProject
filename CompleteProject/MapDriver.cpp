#include "MapDriver.hpp"

using namespace std;
void testLoadMaps(){    MapLoader* LOADER = new MapLoader();
    cout<< "******************** LOAD MAP ******************* \n"<<endl;
    LOADER->ReadDescription("C:\\Users\\bechr\\Documents\\GitHub\\COMP345-WarzoneProject\\all\\working\\map.txt");
    if (*LOADER->m_map_desc == "") return ;
    cout<<*LOADER->m_map_desc;
    LOADER->LoadMap();
    LOADER->m_map->Validate();
    cout<< (LOADER->m_map->m_Continents.size());
    cout << *(LOADER->m_map);}
