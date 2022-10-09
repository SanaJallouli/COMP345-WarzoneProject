#include "MapDriver.hpp"

using namespace std;
void testLoadMaps(){    MapLoader* LOADER = new MapLoader();
    cout<< "******************** LOAD MAP ******************* \n"<<endl;
    LOADER->ReadDescription("map.txt");
    if (*LOADER->m_map_desc == "") return ;
    cout<<*LOADER->m_map_desc;
    LOADER->LoadMap();
    LOADER->m_map->Validate();
    cout << *(LOADER->m_map);}
