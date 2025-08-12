//skeleton
#include <vector>
#include <iostream>
#include <map>

class War {
  public:
    //variables
    std::multimap<std::string, std::string> deck; 
    std::vector<std::pair<std::string,std::string>> shuffling;  

    std::vector<std::pair<std::string,std::string>> p1_Deck;
    std::vector<std::pair<std::string,std::string>> p2_Deck;

    std::vector<std::pair<std::string,std::string>> p1_CardFacingUp;
    std::vector<std::pair<std::string,std::string>> p2_CardFacingUp;

    std::vector<std::pair<std::string,std::string>> p1_CardFacingDown;
    std::vector<std::pair<std::string,std::string>> p2_CardFacingDown;

    std::vector<std::pair<std::string,std::string>> pile;

    bool p1_Won = false;
    bool p2_Won = false;
    bool tie = false;

    //constructor
    War();
    //methods
    void shuffleCards();
    void creating_hands();

    void currentCardP1();
    void currentCardP2();

    void faceDownCardP1();
    void faceDownCardP2();

    bool comparingCards();

    std::string talk(bool p1, bool p2);

};