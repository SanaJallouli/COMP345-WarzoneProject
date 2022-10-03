#pragma once 

#include "Utility_map.h" 

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