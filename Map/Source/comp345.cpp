

#include <iostream>
#include "MapLoader.h"
using namespace std;
int main()
{
    MapLoader* LOADER = new MapLoader();
    LOADER->ReadDescription("C:\\Users\\ambec\\Desktop\\comp345project\\comp345\\1.txt");
    LOADER->LoadMap();
   LOADER->m_map->Validate();


}
