
#include "GameEngine.hpp"
#include "Player.hpp";
#include <list>
using namespace std;

     
void testGameStates(){

    setState(start);
    const char* states[8]={"start","map loaded","map validated","players added","assign reinforcement","issue orders","execute orders","win"};
        cout<<"enter your command"<<endl;
        while(true){
            cin>>tempStr;
            if(tempStr=="win"){
                break;
                
            }
            if(tempStr=="loadmap"){
                cout << "map loaded";
            }
        
         }
