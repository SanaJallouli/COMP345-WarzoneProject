#include "Order.hpp"
using namespace std;

void testOrdersList() {
    cout << "******************** TEST ORDER ******************* \n" << endl;
    Player* a = new Player("a");
Player* b= new Player("b");
a->AllPlayers.insert(a->AllPlayers.begin(), b);
a->AllPlayers.insert(a->AllPlayers.begin(), a);
b->AllPlayers = a->AllPlayers;
Territory* t__1 = new Territory();
t__1->m_name = new string("t_1");
Territory* t__2 = new Territory();
t__2->m_name = new string("t_2");
Territory* t__3 = new Territory();
t__3->m_name = new string("t_3");

t__1->m_Connections.insert(t__1->m_Connections.begin(), t__2);;
t__2->m_Connections.insert(t__2->m_Connections.begin(), t__3);;

cout << "\n******************** Deploy  ******************* \n" << endl;
 a = new Player("a");
 b = new Player("b");
a->AllPlayers.insert(a->AllPlayers.begin(), b);
a->AllPlayers.insert(a->AllPlayers.begin(), a);
b->AllPlayers = a->AllPlayers;
    

}

void TestDeploy() {
    cout << "\n******************** Deploy  ******************* \n" << endl;

    Player* a = new Player("a");
    Player* b = new Player("b");
    a->AllPlayers.insert(a->AllPlayers.begin(), b);
    a->AllPlayers.insert(a->AllPlayers.begin(), a);
    b->AllPlayers = a->AllPlayers;
    Territory* t__1 = new Territory();
    t__1->m_name = new string("t_1");
    Territory* t__2 = new Territory();
    t__2->m_name = new string("t_2");

    a->territories.insert(a->territories.begin(), t__1);
    b->territories.insert(b->territories.begin(), t__2);
    a->armies = new int(60);
    a->orders->addOrder(new Deploy(a, 50, t__1,new Command(), new LogObserver()));
    a->orders->addOrder(new Deploy(a, 5, t__2, new Command(), new LogObserver()));
    a->orders->addOrder(new Deploy(a, 200, t__1,new Command(), new LogObserver()));

    a->execDeploy();

}

void TestAdvance() {
    cout << "\n******************** ADVANCE  ******************* \n" << endl;

    Player* a = new Player("a");
    Player* b = new Player("b");
    a->AllPlayers.insert(a->AllPlayers.begin(), b);
    a->AllPlayers.insert(a->AllPlayers.begin(), a);

    b->AllPlayers.insert(b->AllPlayers.begin(), b);
    b->AllPlayers.insert(b->AllPlayers.begin(), a);

    Territory* t__1 = new Territory();
    t__1->m_name = new string("t_1");
    Territory* t__2 = new Territory();
    t__2->m_name = new string("t_2");
    Territory* t__3 = new Territory();
    t__3->m_name = new string("t_3");


    t__1->m_Connections.insert(t__1->m_Connections.begin(), t__2);;
    t__2->m_Connections.insert(t__2->m_Connections.begin(), t__3);;

    a->territories.insert(a->territories.begin(), t__1);
    t__1->player_owner = new string("a");

    b->territories.insert(b->territories.begin(), t__3);
    t__3->player_owner = new string("b");

    b->territories.insert(b->territories.begin(), t__2);
    t__2->player_owner = new string("b");

    a->armies = new int(60);
    t__1->armies = new int(50);
    t__2->armies = new int(500);
    t__3->armies = new int(500);

    Order* ord = new Advance(a, t__1, 40, t__2, new Command(), new LogObserver());
    ord->execute();

     ord = new Advance(a, t__1, 40, t__3, new Command(), new LogObserver());
    ord->execute();

    ord = new Advance(b, t__2, 40, t__3, new Command(), new LogObserver());
    ord->execute();
    t__1->armies = new int(50000);

    ord = new Advance(a, t__1, 40000, t__2, new Command(), new LogObserver());
    ord->execute();

}


void TestNegociate() {
    cout << "******************** ADVANCE  ******************* \n" << endl;

    Player* a = new Player("a");
    Player* b = new Player("b");
    a->AllPlayers.insert(a->AllPlayers.begin(), b);
    a->AllPlayers.insert(a->AllPlayers.begin(), a);

    b->AllPlayers.insert(b->AllPlayers.begin(), b);
    b->AllPlayers.insert(b->AllPlayers.begin(), a);

    Territory* t__1 = new Territory();
    t__1->m_name = new string("t_1");
    Territory* t__2 = new Territory();
    t__2->m_name = new string("t_2");
    Territory* t__3 = new Territory();
    t__3->m_name = new string("t_3");


    t__1->m_Connections.insert(t__1->m_Connections.begin(), t__2);;
    t__2->m_Connections.insert(t__2->m_Connections.begin(), t__3);;

    a->territories.insert(a->territories.begin(), t__1);
    t__1->player_owner = new string("a");

    b->territories.insert(b->territories.begin(), t__3);
    t__3->player_owner = new string("b");

    b->territories.insert(b->territories.begin(), t__2);
    t__2->player_owner = new string("b");

    a->armies = new int(60);
    t__1->armies = new int(50);
    t__2->armies = new int(500);
    t__3->armies = new int(500);

    Order* ord = new Negotiate(a,b, new Command(), new LogObserver());
    ord->execute();

        ord = new Advance(a, t__1, 40, t__2, new Command(), new LogObserver());
    ord->execute();

    ord = new Advance(a, t__1, 40, t__3, new Command(), new LogObserver());
    ord->execute();

    ord = new Advance(b, t__2, 40, t__3, new Command(), new LogObserver());
    ord->execute();
    t__1->armies = new int(50000);

    ord = new Advance(a, t__1, 40000, t__2, new Command(), new LogObserver());
    ord->execute();

}

void TestBlockade() {
    cout << "******************** Blockade  ******************* \n" << endl;

    Player* a = new Player("a");
    Player* b = new Player("b");
    a->AllPlayers.insert(a->AllPlayers.begin(), b);
    a->AllPlayers.insert(a->AllPlayers.begin(), a);

    b->AllPlayers.insert(b->AllPlayers.begin(), b);
    b->AllPlayers.insert(b->AllPlayers.begin(), a);

    Territory* t__1 = new Territory();
    t__1->m_name = new string("t_1");
    Territory* t__2 = new Territory();
    t__2->m_name = new string("t_2");
    Territory* t__3 = new Territory();
    t__3->m_name = new string("t_3");


    t__1->m_Connections.insert(t__1->m_Connections.begin(), t__2);;
    t__2->m_Connections.insert(t__2->m_Connections.begin(), t__3);;

    a->territories.insert(a->territories.begin(), t__1);
    t__1->player_owner = new string("a");



    t__1->armies = new int(50);

    a->Neutral = new Player("neutral");
    Order* ord = new Blockade(a, t__1, new Command(), new LogObserver());
    ord->execute();

}