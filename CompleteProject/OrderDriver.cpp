#include "Order.hpp"
using namespace std;

void testOrdersList() {
    cout << "******************** TEST ORDER ******************* \n" << endl;
    OrdersList* anOrderList = new OrdersList();

    Deploy* deploy = new Deploy();
    Advance* advance = new Advance();
    Bomb* bomb = new Bomb();
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
        cout << "  " << *((anOrderList->get_order_list().at(i))->get_type()) << endl;
    }

    //delete order
    cout << "\ndeleting an order :" << endl;
    anOrderList->remove(anOrderList->get_order_list().at(5));

    //print orderlist
    cout << "\nthe orderlist contains: " << endl;
    for (int i = 0; i < (anOrderList->get_order_list()).size(); i++) {
        cout << "  " << *((anOrderList->get_order_list().at(i))->get_type()) << endl;
    }

    //move order
    cout << "\nmoving order with coordinates x = 1, y = 3:" << endl;
    int coorX = 1;
    int coorY = 3;
    anOrderList->move(coorX, coorY);
    //print orderlist
    cout << "\nthe orderlist contains: " << endl;
    for (int i = 0; i < (anOrderList->get_order_list()).size(); i++) {
        cout << "  " << *((anOrderList->get_order_list().at(i))->get_type()) << endl;
    }
}