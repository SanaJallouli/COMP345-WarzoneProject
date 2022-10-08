<<<<<<< HEAD

#include "GameEngine.hpp"
#include "Player.hpp";
#include <list>
using namespace std;

     
//void testGameStates(){
//
//    setState(start);
//    const char* states[8]={"start","map loaded","map validated","players added","assign reinforcement","issue orders","execute orders","win"};
//        cout<<"enter your command"<<endl;
//        while(true){
//            cin>>tempStr;
//            if(tempStr=="win"){
//                break;
//                
//            }
//            if(tempStr=="loadmap"){
//                cout << "map loaded";
//            }
//        
//         }
=======
// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameEngine.h"

int testGameStates()
{
    GameEngine* ge=new GameEngine() ;
    ge->manage();
   
}

>>>>>>> 3600317 (gameengine)
