#include "PLayer.hpp"
#include "Cards.hpp"
#include <iostream>
using namespace std;


void testCards() {
    cout << "============= testCards() Start ================" << endl
            << "." << endl << "." << endl;

    //simple deck of 5 cards, one card of each type
    Deck* deck = new Deck();
    cout << *deck << endl;

    //Draw 5 random cards one at a time
    //card 1
    Card* card1 = deck->draw();
    cout << "draw 1: " << *card1;
    cout << *deck << endl;
    //card 2
    Card* card2 = deck->draw();
    cout << "draw 2: " << *card2;
    cout << *deck << endl;
    //card 3
    Card* card3 = deck->draw();
    cout << "draw 3: " << *card3;
    cout << *deck << endl;
    //card 4
    Card* card4 = deck->draw();
    cout << "draw 4: " << *card4;
    cout << *deck << endl;
    //card 5
    Card* card5 = deck->draw();
    cout << "draw 5: " << *card5;
    cout << *deck << endl;

    //add card1 to hand1
    Hand * hand1 = new Hand();
    cout << "create hand: " << endl << *hand1 << endl;
    hand1->addCardHand(card1);
    cout << "add card1 to hand" << endl<< *hand1 << endl;

    //add cards 2 to 5 to hand
    cout << "adding cards 2 to 5 to hand" << endl;
    hand1->addCardHand(card2);
    hand1->addCardHand(card3);
    hand1->addCardHand(card4);
    hand1->addCardHand(card5);
    cout << *hand1 << endl;

    //create player with a copy of hand1
    Player* player1 = new Player("player1");
    cout << *player1->m_name << " " << endl << *player1->hand;
    player1->hand = hand1;//deep copy of hand1 performed here
    cout << *player1->m_name << " " << endl << *player1->hand;

    //play each card in hand
    cout << endl << "Player1 plays bomb card:" << endl;
    player1->hand->play(pBOMB,deck,player1);
    cout << *player1->hand << *deck;
    cout << endl << "Player1 plays blockade card:" << endl;
    player1->hand->play(pBLOCKADE, deck, player1);
    cout << *player1->hand << *deck;
    cout << endl << "Player1 plays reinforcement card:" << endl;
    player1->hand->play(pREINFORCEMENT, deck, player1);
    cout << *player1->hand << *deck;
    cout << endl << "Player1 plays airlift card:" << endl;
    player1->hand->play(pAIRLIFT, deck, player1);
    cout << *player1->hand << *deck;
    cout << endl << "Player1 plays diplomacy card:" << endl;
    player1->hand->play(pDIPLOMACY, deck, player1);
    cout << *player1->hand << *deck;

    //print out of player's list of order
    std::list<Order*>::iterator iter;
    string* s;
    cout << endl << "Player's list of orders contains: " << endl;
    for (iter = player1->orders.begin(); iter != player1->orders.end(); iter++) {
        s = (*iter)->get_type();
        cout << *s << " ";
    }
    s = nullptr;

    //shows a deep copy was performed
    cout << endl << "Player1 has :" << *player1->hand << " while original hand1 still has "
        << endl << *hand1;


    cout << "." << endl << "." << endl
        << "============= testCards() End ================" << endl;     
};
