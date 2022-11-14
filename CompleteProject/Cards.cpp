#include "PLayer.hpp"
#include "Cards.hpp"
#include <string>
#include <time.h>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;
                
//const pointer to const char[] for card creation
const char* const pBOMB = "Bomb";
const char* const pREINFORCEMENT = "Reinforcement";
const char* const pBLOCKADE = "Blockade";
const char* const pAIRLIFT = "Airlift";
const char* const pDIPLOMACY = "Diplomacy";

//static cards of different types needed to create a full deck
static Card* pCard1 (NULL);
static Card* pCard2 (NULL);
static Card* pCard3 (NULL);
static Card* pCard4 (NULL);
static Card* pCard5 (NULL);

//========================================== Class Card =========================================================

/**
* Default constructor, creates a Card object with a randomly chosen type.
* Type can be: "Bomb", "Reinforcement", "Blockade", "Airlift", or "Diplomacy".
*/
Card::Card(){
    pCardTypeString = NULL;
    srand(time(0)); //seed rand with the current time
    int type = (rand() % 5) + 1; //random number 1 to 5
    switch (type){
    case 1:
        pCardTypeString = new string(pBOMB);
        break;
    case 2:
        pCardTypeString = new string(pREINFORCEMENT);
        break;
    case 3:
        pCardTypeString = new string(pBLOCKADE);
        break;
    case 4:
        pCardTypeString = new string(pAIRLIFT);
        break;
    case 5:
        pCardTypeString = new string(pDIPLOMACY);
        break;
    }
}

/**
* Creates a pointer to a card object with the specified type.
* \param cardType : must a char[]*, use one of the global const pointers:
*        pBOMB, pREINFORCEMENT, pBLOCKADE, pAIRLIFT or pDIPLOMACY
*/
Card::Card(const char* cardType){
    pCardTypeString = new string (cardType);
}

/**
* Destructor of Card class.
*
*/
Card::~Card() {
    delete pCardTypeString;
    pCardTypeString = NULL;
}
    
/**
* Card class deep copy constructor.
*
*/
Card::Card(const Card& c) {
    this->pCardTypeString = new string(*(c.pCardTypeString));
}

/**
 * Overloaded Card class = operator.
 */
Card& Card::operator=(const Card& c) {
    this->pCardTypeString = new string(*(c.pCardTypeString));
    return *this;
}

/**
* Card class stream operator.
* Outputs the card type.
*/
ostream& operator<<(ostream& output, const Card& c) {
    if (&c != NULL) return output << "Card(" << *c.pCardTypeString << ")" << std::endl;
    else return output << "NULL" << std::endl;
}

/**
 * String representing the card type (i.e Bomb).
 *
 * \return string ref
 */
string &Card::getCardTypeString() {
    return *pCardTypeString;
}


//========================================= Class Deck ===========================================================

/**
* Default constructor, should not be explicity called.
* Creates a deck with one of each card type.
*/
Deck::Deck(){
    pDeckV = new std::vector<Card*>(5);

    //create one instance of each card type
    pCard1 = new Card(pBOMB);
    pCard2 = new Card(pREINFORCEMENT);
    pCard3 = new Card(pBLOCKADE);
    pCard4 = new Card(pAIRLIFT);
    pCard5 = new Card(pDIPLOMACY);

    //add cards to deck
    pDeckV->at(0) = pCard1;
    pDeckV->at(1) = pCard2;
    pDeckV->at(2) = pCard3;
    pDeckV->at(3) = pCard4;
    pDeckV->at(4) = pCard5;
}

/**
* Creates a Deck object which contains a vector of pointers of
* card types.
* Deck will be filled with random Card object pointers.
*
* THIS SHOULD BE THE ONLY deck object in the game.
*
* \param size : int must be >= 5
*/
Deck::Deck(int size){

    //create one instance of each card type
    pCard1 = new Card(pBOMB);
    pCard2 = new Card(pREINFORCEMENT);
    pCard3 = new Card(pBLOCKADE);
    pCard4 = new Card(pAIRLIFT);
    pCard5 = new Card(pDIPLOMACY);

    //pointer to created vector on the heap
    pDeckV = new std::vector<Card*>(size);

    //populate the deck with random card pointers
    int type = 0;
    srand(time(0)); //seed rand with the current time
    for (int i = 0; i < size; i++) {
        type = ((1+i) /*rand()*/ % 5) + 1; //random number 1 to 5
        switch (type) {
        case 1:
            pDeckV->at(i) = pCard1;
            break;
        case 2:
            pDeckV->at(i) = pCard2;
            break;
        case 3:
            pDeckV->at(i) = pCard3;
            break;
        case 4:
            pDeckV->at(i) = pCard4;
            break;
        case 5:
            pDeckV->at(i) = pCard5;
            break;
        }
    }
}

/**
* Deck class destructor.
*
*/
Deck::~Deck() {
    delete pCard1;
    delete pCard2;
    delete pCard3;
    delete pCard4;
    delete pCard5;
    pCard1 = NULL;
    pCard2 = NULL;
    pCard3 = NULL;
    pCard4 = NULL;
    pCard5 = NULL;

    delete pDeckV;
    pDeckV = NULL;
}

/**
* Deck class deep copy constructor.
*
*/
Deck::Deck(const Deck& d) {
    //deep copy of vector containing pointers
    int size = d.pDeckV->size();
    this->pDeckV = new std::vector<Card*>(size);
    for (int i = 0; i < size; i++) {
        this->pDeckV->at(i) = d.pDeckV->at(i);
    }
}

/**
* Overloaded Deck class = operator.
*/
Deck& Deck::operator=(const Deck& d) {
    //deep copy of vector containing pointers
    int size = d.pDeckV->size();
    this->pDeckV = new std::vector<Card*>(size);
    for (int i = 0; i < size; i++) {
        this->pDeckV->at(i) = d.pDeckV->at(i);
    }
    return *this;
}

/**
* Deck class stream operator.
* Outputs the deck size and contents.
*/
ostream& operator << (ostream& output, const Deck& d) {
    output << "Deck size: " << d.pDeckV->size() << std::endl << "Deck(";
    for (int i = 0; i < d.pDeckV->size(); i++) {
        output << i << ":";
        if (d.pDeckV->at(i) != NULL) output << d.pDeckV->at(i)->getCardTypeString() << " ";
        else output << "NULL ";
    }
    return output << ")" << std::endl;
}


/**
* Picks and removes random card pointer from the deck.
* Returns the card pointer.
*/
Card* Deck::draw() {
    Card* pDeckCard (NULL);
    srand(time(0));
    int cardIndex(0);

    //pick random card in deck
    cardIndex =1/*rand()*/ % pDeckV->size(); //random index over entire array
    if (pDeckV->at(cardIndex) != NULL) {
        pDeckCard = pDeckV->at(cardIndex);
        pDeckV->erase(pDeckV->begin() + cardIndex);
    }
    return pDeckCard;
}

/**
 * Add card pointer into deck.
 *
 * \param c
 */
void Deck::addCardDeck(Card* c) {
    pDeckV->push_back(c);
}

//========================================== Class Hand ==========================================================

/**
 * Default constructor.
 * Creates a Hand object with no cards.
 */
Hand::Hand() {
    pHandList = new std::list<Card*>();
 //   order = new Order();
}

/**
 * Hand destructor.
 */
Hand::~Hand() {
    delete pHandList;
    pHandList = NULL;
    delete order;
    order = NULL;
}

/**
 *  Deep copy constructor for Hand class.
 */
Hand::Hand(const Hand& h) {
    this->pHandList = new std::list<Card*>();
    
    //need to iterate over list of pointers for a deep copy
    if (!h.pHandList->empty()) {
        std::list<Card*>::const_iterator iter;
        for (iter = h.pHandList->begin(); iter != h.pHandList->end(); iter++) {
            pHandList->push_back(*iter);
        }
    }
  //  this->order = new Order(*(h.order));
}

/**
 * Overloaded = for Hand objects.
 */
 Hand& Hand::operator=(const Hand& h) {
     this->pHandList = new std::list<Card*>();

     //need to iterate over list of pointers for a deep copy
     if (!h.pHandList->empty()) {
         std::list<Card*>::const_iterator iter;
         for (iter = h.pHandList->begin(); iter != h.pHandList->end(); iter++) {
             pHandList->push_back(*iter);
         }
     }
     //this->order = new Order(*(h.order));
     return *this;
}

 /**
  * Overloaded << for Hand objects.
  * Prints the cards in the hand.
  */
 ostream& operator << (ostream& output, const Hand& h) {
     output << "Hand (";
     if (h.pHandList->empty()) output << "EMPTY ";
     else {
         std::list<Card*>::const_iterator iter;
         for (iter = h.pHandList->begin(); iter != h.pHandList->end(); iter++) {
             output << (*iter)->getCardTypeString() << " ";
         }
     }
     return output << ")" << std::endl;
 }

 /**
  * Adds the card pointer into hand.
  *
  * \param card pointer
  */
 void Hand::addCardHand(Card* card) {
     pHandList->push_back(card);
 }

 /**
  * Removes card pointer from the hand if it exists and returns it.
  * Returns null if hand does not contain a pointer
  * of the specified type or hand is empty.
  * \param use the global const pointers: pBOMB, pREINFORCEMENT, pBLOCKADE, pAIRLIFT or pDIPLOMACY
  */
 Card* Hand::removeCard(const char* cardType) {
     Card* pCard = NULL;
     string s;

     //iterate over list, remove and return card pointer at the first occurance found
     if (!pHandList->empty()) {
         std::list<Card*>::iterator iter;
         for (iter = pHandList->begin(); iter != pHandList->end(); iter++) {
             s = (*iter)->getCardTypeString();
             if (s==cardType){
                 pCard = *iter;
                 pHandList->erase(iter);
                 break;
             }
         }         
     }
     return pCard;
 }

 /**
  * Removes card pointer from the hand if it exists, creates order based on the card
  * type, and adds the card pointer into the deck.
  * \param cardType use the global const pointers: pBOMB, pREINFORCEMENT, pBLOCKADE, pAIRLIFT or pDIPLOMACY
  * \param d pointer to a Deck object
  */
 void Hand::play(const char* cardType, Deck* d, Player* p){
   //  order = new Order();
     Card* card = removeCard(cardType);
     if (card != NULL) {
         int type = cardToOrderType(cardType);//map card type to order
         switch (type) {
         case 2:
             order->set_type_id(2);
             break;
         case 3:
             order->set_type_id(3);
             break;
         case 4:
             order->set_type_id(4);
             break;
         case 5:
             order->set_type_id(5);
             break;
         }
         //only create orders for bomb, blockade, airlift and negotiate (diplomacy card)
         if (type > 1 && type < 6) {
             p->orders->order_list.push_back(order); //add to player's list of orders
             cout << "order " << *order->get_type() << " created, added to player's orders." << endl;
         }
         d->addCardDeck(card);//add card to deck
     }
 }

 //==================== free functions ===========================================

 /**
  * Use to create the appropriate Order given the card type.
  * 
  * \param cardType use global const pointers: pBOMB, pREINFORCEMENT, pBLOCKADE, pAIRLIFT or pDIPLOMACY
  * \returns int representing Order type
  */
 int cardToOrderType(const char* cardType){
     string s = cardType;
     int type = 0;

     if (s == pBOMB) type = 2;
     else if (s == pBLOCKADE) type = 3;
     else if (s == pAIRLIFT) type = 4;
     else if (s == pDIPLOMACY) type = 5;

     return type;
 }
