#include "PLayer.hpp"
#include "Cards.hpp"
#include <iostream>
using namespace std;


void testCards() {
    cout << "============= testCards() Start ================" << endl
            << "." << endl << "." << endl;

    //simple deck of 5 cards, one card of each type
    Deck deck = Deck();
    cout << deck << endl;

    //Draw 5 random cards one at a time
    //card 1
    Card* card1 = deck.draw();
    cout << "draw 1: " << *card1;
    cout << deck << endl;
    //card 2
    Card* card2 = deck.draw();
    cout << "draw 2: " << *card2;
    cout << deck << endl;
    //card 3
    Card* card3 = deck.draw();
    cout << "draw 3: " << *card3;
    cout << deck << endl;
    //card 4
    Card* card4 = deck.draw();
    cout << "draw 4: " << *card4;
    cout << deck << endl;
    //card 5
    Card* card5 = deck.draw();
    cout << "draw 5: " << *card5;
    cout << deck << endl;

    //add card1 to hand1
    Hand hand1 = Hand();
    cout << "create hand: " << endl << hand1 << endl;
    hand1.addCardHand(card1);
    cout << "add card1 to hand" << endl<< hand1 << endl;

    //add cards 2 to 5 to hand
    cout << "add cards 2 to 5 to hand" << endl;
    hand1.addCardHand(card2);
    hand1.addCardHand(card3);
    hand1.addCardHand(card4);
    hand1.addCardHand(card5);
    cout << hand1 << endl;

    Player player1 = Player("player1");
    cout << *player1.m_name << " " << endl << player1.hand;
    player1.hand = hand1;
    cout << *player1.m_name << " " << endl << player1.hand;


    cout << "." << endl << "." << endl
        << "============= testCards() End ================" << endl;
        
};
