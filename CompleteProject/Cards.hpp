#pragma once
#include <string>
#include <vector>
#include <list>

using std::string;
using std::ostream;
class Player;
class Order;

extern const char* const pBOMB;
extern const char* const pREINFORCEMENT;
extern const char* const pBLOCKADE;
extern const char* const pAIRLIFT;
extern const char* const pDIPLOMACY;

class Card {
public:
    Card();
    Card(const char* type);
    ~Card();
    Card(const Card& c);

    Card& operator = (const Card& c);
    friend ostream& operator << (ostream& output, const Card& c);

    string &getCardTypeString();
    
private:
    string* pCardTypeString;
};

class Deck {
public:
    Deck();
    Deck(int size);
    ~Deck();
    Deck(const Deck& d);

    Deck& operator = (const Deck& d);
    friend ostream& operator << (ostream& output, const Deck& d);
    
    Card* draw();
    void addCardDeck(Card* c);
private:
    std::vector<Card*> * pDeckV;
};

class Hand {
public:
    Hand();
    ~Hand();
    Hand(const Hand& h);
    Order* order;

    Hand& operator = (const Hand& h);
    friend ostream& operator << (ostream& output, const Hand& h);

    void addCardHand(Card* c);
    Card* removeCard(const char* cardType);
    void play(const char* cardType, Deck* d, Player* p);
    std::list<Card*>* pHandList;


};

int cardToOrderType(const char* cardType);