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

}