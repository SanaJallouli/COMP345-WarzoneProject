// comp345.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Map.h"

using namespace std;
int  main() 
{
    MapLoader* LOADER = new MapLoader();
    LOADER->ReadDescription("scores.txt");
    LOADER->LoadMap();
    LOADER->m_map->Validate();
    cout << *(LOADER->m_map);
}

