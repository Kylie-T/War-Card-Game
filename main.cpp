#include "war.hpp"
#include <iostream>

int main() {
    War Game;
    Game.creating_hands();
    int turns = 0;

    while (Game.p1_Deck.size() != 0 && Game.p2_Deck.size() != 0 ){
        Game.comparingCards();
        std::cout << Game.talk(Game.p1_Won, Game.p2_Won) << "\n";
        std::cout << "P1 size: " << Game.p1_Deck.size()
          << " | P2 size: " << Game.p2_Deck.size() << "\n\n";
        turns += 1;
        if (Game.tie == true){
            turns -= 1;
        }

    }
    if (Game.p1_Deck.size() == 0) {
        std::cout << "Player 2 won the war!\n";
    } 
    else if (Game.p2_Deck.size() == 0) {
        std::cout << "Player 1 won the war!\n";
    }
    std::cout << "This game took " << turns << " turns.\n";
    
}