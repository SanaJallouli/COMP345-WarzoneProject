
#include "Player.hpp"

using namespace std;


list<Territory*> Player::toDefend(){
    cout<<"toDefend method working \n";
    Territory* terr = new Territory();
    list<Territory*> randomTerr;
    randomTerr.insert(randomTerr.begin(),terr);
    return randomTerr;
};


list<Territory*> Player::toAttack(){
    cout<<"toAttack method working \n";
    Territory* terr = new Territory();
    list<Territory*> randomTerr;
    randomTerr.insert(randomTerr.begin(),terr);
    return randomTerr;
};

Card* getCard(list<Card*>* l, string card_name) {
        std::list<Card*>::iterator it;
        for (it = (*l).begin(); it != (*l).end(); ++it) {

            if (card_name == (*it)->getCardTypeString()) {
                return (*it);
            }
        }
        return nullptr; 
}

Player* getplayer(list<Player*> l, string card_name) {
    std::list<Player*>::iterator it;
    for (it = l.begin(); it != l.end(); ++it) {

        if (card_name == *(*it)->m_name) {
            return (*it);
        }
    }
    return nullptr;
}

bool isNumber(const string& s)
{
    for (char const& ch : s) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}
bool Player::issueOrder() {
    cout << "Player : " << *m_name << " Turn started  " << endl;
    if (*armies > *deployed_inTurn) {
        while (true) {
            cout << "Player : " << *m_name << " has " << *armies << endl;
            cout << "Possible action are  : deploy ( command :deploy territory_name nbr_army)  " << *territories.front()->m_name<< endl;

            Command c = cP->getCommand();
            string command = c.getCommand();
            string com = string(command.substr(0, command.find(" ")));
            string arg = string(command.substr(command.find(" ") + 1));
            string territory_name = string(arg.substr(0, arg.find(" ")));
            string  nbr_armies = string(arg.substr(arg.find(" ") + 1));

            cout << command<<endl;
            if (isNumber(nbr_armies) && getTerritory(territories, territory_name)!=nullptr) {
                int i = std::stoi(nbr_armies);
                *deployed_inTurn = *deployed_inTurn + i;
                orders.insert(orders.end(), new Deploy(this, i, getTerritory(territories, territory_name)));
                return true;
            }
            cout << "The command written is error either territory does not exist or armies is not digit" << endl;
        }
    }

    while (true) {
        //Advance(Player* p, Territory* Source, int t, Territory* Destination) : Order(p)
        cout << "Player : " << *m_name << " has " << *armies << endl;
        cout << "Possible action are  : advance  (command :advance territory_owned nbr_army ter_desti) " ;
        Card* card = getCard(hand->pHandList, "Bomb");
        if (card != nullptr)
            cout << ", bomb  (command :bomb ter_desti) ";

        card = getCard(hand->pHandList, "Airlift");
        if (card != nullptr)
            cout << ", airlift  (command :airlift territory_owned nbr_army ter_desti) ";

         card = getCard(hand->pHandList, "Blockade");
        if (card != nullptr)
            cout << ", blockade  (command :blockade ter_desti) ";
        card = getCard(hand->pHandList, "Diplomacy");
        if (card != nullptr)
            cout << ", blockade  (command :negociate player_NAME) ";;

            cout << ", end (to choose not to make another turn ) ";;

        cout << endl;
   
       Command c = cP->getCommand();
        string command=c.getCommand();

        cout << command << endl;
        string com = string(command.substr(0, command.find(" ")));
        string arg = string(command.substr(command.find(" ") + 1));
       
            if (com == "advance" || com == "airlift" ) {

            string territory_name = string(arg.substr(0, arg.find(" ")));
              arg = string(arg.substr(arg.find(" ") + 1));
              string nbr_armies = string(arg.substr(0, arg.find(" ")));
              string destination= string(arg.substr(arg.find(" ") + 1));
              if (com == "advance") {
                  orders.insert(orders.end(), new Advance(this, getTerritory(territories, territory_name),std::stoi(nbr_armies), getTerritory(territories, destination)));
                  return true;;
              }
              if (com == "airlift") {
                  orders.insert(orders.end(), new Airlift(this, getTerritory(territories, territory_name),std::stoi(nbr_armies), getTerritory(territories, territory_name)));
                  return true;;
              }
        }
            if (com == "blockade") {
                orders.insert(orders.end(), new Blockade(this, getTerritory(territories, arg)));

                return true;
            }  
            if (com == "negociate") {
                orders.insert(orders.end(), new Negotiate(this, getplayer(AllPlayers, arg)));

                return true;
            }
                if (com == "bomb") {
                    orders.insert(orders.end(), new Bomb(this, getTerritory(territories, arg)));

                    return true;;
            }
      
       
                if (com == "end") {
                    return false;
                }

    }
 
    return true;
}

void Player::execDeploy() {
    std::list<Order*>::iterator it;
    for (it = orders.begin(); it != orders.end(); ++it) {
        if (*(*it)->get_type() == "Deploy") {
            (*it)->execute();     
            orders.remove(*it);
        }

    }
}

 Player::Player(const Player& player){
     m_name = new string(*player.m_name);
     territories = list<Territory*>(player.territories);
     cards =  list<Card*>(player.cards);
     orders = list<Order*>(player.orders);
     hand = new Hand(*(player.hand));

}

Player::Player(){
    m_name = new string();
    hand = new Hand();
     territories = list<Territory*>();;
     cards = list<Card*>();
     orders= list<Order*>();

}; //default constructor


Player::Player(string name){
    m_name = new string(name);
    hand = new Hand();
     territories = list<Territory*>();;
     cards = list<Card*>();
     orders= list<Order*>();

}; // constructor

Player::~Player() {
    delete m_name;//deallocate
    m_name = nullptr; // avoid dangling pointers
    delete hand;
    hand = nullptr;
    for (std::list<Territory*>::iterator it = territories.begin(); it != territories.end(); ++it) {
        delete *it;
        *it= nullptr;
    }
    for (std::list<Card*>::iterator it = cards.begin(); it != cards.end(); ++it) {
        delete *it;
        *it= nullptr;
    }
    for (std::list<Order*>::iterator it = orders.begin(); it != orders.end(); ++it) {
        delete *it;
        *it= nullptr;
    }

}

//cout operator
ostream& operator<<(ostream &strm, const Player& player) {
   return strm << "Player Name " << *player.m_name ;};

// assignment operator 
Player& Player::operator=(const Player &player)
 {
  
    this->m_name = new string(*player.m_name);
    this-> territories = list<Territory*>(player.territories);
    this->cards =  list<Card*>(player.cards);
    this->orders = list<Order*>(player.orders);
    this->hand = new Hand(*(player.hand));
   return *this;};


