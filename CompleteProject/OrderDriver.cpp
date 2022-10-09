#include "Order.hpp"
using namespace std;

void testOrdersList(){
    cout<< "******************** TEST CARDS ******************* \n" << endl;
    OrdersList* anOrderList = new OrdersList();

    Deploy* deploy = new Deploy();
    Advance* advance= new Advance();
    Bomb* bomb =new Bomb();
    Blockade* blockade = new Blockade();
    Airlift* airlift = new Airlift();
    Negotiate* negotiate = new Negotiate();

    anOrderList->set_order_list(deploy);
    anOrderList->set_order_list(advance);
    anOrderList->set_order_list(bomb);
    anOrderList->set_order_list(blockade);
    anOrderList->set_order_list(airlift);
    anOrderList->set_order_list(negotiate);


    //print orderlist
    cout << "\nthe orderlist contains: " << endl;
    for (int i = 0; i < anOrderList->get_order_list().size(); i++) {
        cout <<"  "<< *((anOrderList->get_order_list().at(i))->get_type()) << endl;
    }

    cout<<"\ndeleting an order :"<<endl;
    cout<<"Enter an order to be removed"<<endl;
    string input;
    cin>>input;
    bool exist=false;
    for ( int i = 0 ; i < (anOrderList->get_order_list()).size();i++){
        if(input ==*((anOrderList->get_order_list().at(i))->get_type())){
            anOrderList->remove(((anOrderList->get_order_list().at(i))));
            exist=true;
            break;
        }
        
    }
    if(exist==false){
        cout<<"Order is not within the orders defined !"<<endl;
    }
    
    

    //print orderlist
    cout << "\nthe orderlist contains: " << endl;
    for ( int i = 0 ; i < (anOrderList->get_order_list()).size();i++) {
        cout <<"  "<< *((anOrderList->get_order_list().at(i))->get_type()) << endl;
    }

    cout<<"\nmoving an order :"<<endl;
    cout<<"Enter coordinates to move :"<<endl;
    int coorX;
    int coorY;
    cout<<"X coordinate:"; cin>> coorX;
    cout<<"\nY coordinate:"; cin>> coorY;
    anOrderList->move(coorX,coorY);
    //print orderlist
    cout << "\nthe orderlist contains: " << endl;
    for ( int i = 0 ; i < (anOrderList->get_order_list()).size();i++){
        cout <<"  "<< *((anOrderList->get_order_list().at(i))->get_type()) << endl;
    }
}
