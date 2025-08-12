#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <chrono>
#include <random>
#include "war.hpp"

//constructor
War::War() 
:
    deck{
        {"a","hearts"}, {"a","diamonds"}, {"a","spades"}, {"a","clubs"},
        {"k","hearts"}, {"k","diamonds"}, {"k","spades"}, {"k","clubs"},
        {"q","hearts"}, {"q","diamonds"}, {"q","spades"}, {"q","clubs"},
        {"j","hearts"}, {"j","diamonds"}, {"j","spades"}, {"j","clubs"},
        {"10","hearts"}, {"10","diamonds"}, {"10","spades"}, {"10","clubs"},
        {"9","hearts"}, {"9","diamonds"}, {"9","spades"}, {"9","clubs"},
        {"8","hearts"}, {"8","diamonds"}, {"8","spades"}, {"8","clubs"},
        {"7","hearts"}, {"7","diamonds"}, {"7","spades"}, {"7","clubs"},
        {"6","hearts"}, {"6","diamonds"}, {"6","spades"}, {"6","clubs"},
        {"5","hearts"}, {"5","diamonds"}, {"5","spades"}, {"5","clubs"},
        {"4","hearts"}, {"4","diamonds"}, {"4","spades"}, {"4","clubs"},
        {"3","hearts"}, {"3","diamonds"}, {"3","spades"}, {"3","clubs"},
        {"2","hearts"}, {"2","diamonds"}, {"2","spades"}, {"2","clubs"}
    }
    {
    p1_Won = false;
    p2_Won = false;
    tie = false;
    shuffling;
    p1_Deck, p2_Deck, p1_CardFacingUp, p2_CardFacingUp,
    p1_CardFacingDown, p2_CardFacingDown, pile;
    }
//methods
void War::shuffleCards() {
    for (auto& pair : deck) {
        // adding pairs from map to vector to shuffle it
        shuffling.push_back(pair);
    }
    // making random ber generator for shuffling
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(shuffling.begin(), shuffling.end(), rng);
}
void War::creating_hands() {
    // shuffle deck first
    shuffleCards();

    //deck for player 1
    for (int i = 0; i < 26; i++) {
        p1_Deck.push_back(shuffling.back());
        shuffling.pop_back();
    }
    //deck for player 2
    for (int j = 0; j < 26; j++){
        p2_Deck.push_back(shuffling.back());
        shuffling.pop_back();
    }
}
// draws for player 1
void War::currentCardP1() {
    p1_CardFacingUp.push_back(p1_Deck[0]);
    p1_Deck.erase(p1_Deck.begin());
}
// draws for player 1
void War::currentCardP2() {
    p2_CardFacingUp.push_back(p2_Deck[0]);
    p2_Deck.erase(p2_Deck.begin());
}

void War::faceDownCardP1() {
    p1_CardFacingDown.push_back(p1_Deck[0]);
    p1_Deck.erase(p1_Deck.begin());
}

void War::faceDownCardP2() {
    p2_CardFacingDown.push_back(p2_Deck[0]);
    p2_Deck.erase(p2_Deck.begin());
}

bool War::comparingCards() {
    //initializing functions to draw cards and resetting variables
    p1_Won = false;
    p2_Won = false;
    tie = false;

    currentCardP1();
    currentCardP2();

    //"q" and "k" are specifically compared because the q has a higher ascii value than k
    //they are comparing ascii values since it is comparing strings
    if (p1_CardFacingUp[0].first > p2_CardFacingUp[0].first) {
        if (p1_CardFacingUp[0].first == "q" && p2_CardFacingUp[0].first == "k") {
            //add p1 face card to p2 deck
            p2_Deck.push_back(p1_CardFacingUp[0]);
            p2_Deck.push_back(p2_CardFacingUp[0]);
            while (pile.empty() == false) {
                p2_Deck.push_back(pile[0]);
                pile.erase(pile.begin());
                }
            //erases p1 face card from deck;
            p1_CardFacingUp.clear();
            p2_CardFacingUp.clear();
            p2_Won = true;
            } else {
            //add p2 face card to p1 deck
            p1_Deck.push_back(p2_CardFacingUp[0]);
            p1_Deck.push_back(p1_CardFacingUp[0]);
            while (pile.empty() == false) {
                p1_Deck.push_back(pile[0]);
                pile.erase(pile.begin());
                }
            }
            //erases p1 face card from deck;
            p1_CardFacingUp.clear();
            p2_CardFacingUp.clear();
            p1_Won = true;
    }
    else if (p1_CardFacingUp[0].first < p2_CardFacingUp[0].first) {
        if (p1_CardFacingUp[0].first == "k" && p2_CardFacingUp[0].first == "q") {
            //add p2 face card to p1 deck
            p1_Deck.push_back(p2_CardFacingUp[0]);
            p1_Deck.push_back(p1_CardFacingUp[0]);
            while (pile.empty() == false) {
                p1_Deck.push_back(pile[0]);
                pile.erase(pile.begin());
                }
            //erases p1 face card from deck;
            p1_CardFacingUp.clear();
            p2_CardFacingUp.clear();
            p1_Won = true;
        } else {
            //add p1 face card to p2 deck
            p2_Deck.push_back(p1_CardFacingUp[0]);
            p2_Deck.push_back(p2_CardFacingUp[0]);
            while (pile.empty() == false) {
                p2_Deck.push_back(pile[0]);
                pile.erase(pile.begin());
                }
            }
            //erases p1 face card from deck;
            p1_CardFacingUp.clear();
            p2_CardFacingUp.clear();
            p2_Won = true;
        }
    else if (p1_CardFacingUp[0].first == p2_CardFacingUp[0].first) {
        faceDownCardP1();
        faceDownCardP2();
        
        pile.push_back(p1_CardFacingUp[0]);
        pile.push_back(p2_CardFacingUp[0]);
        pile.push_back(p1_CardFacingDown[0]);
        pile.push_back(p2_CardFacingDown[0]);

        p1_CardFacingUp.clear();
        p2_CardFacingUp.clear();
        p1_CardFacingDown.clear();
        p2_CardFacingDown.clear();

        tie = true;
    } 

    return p1_Won || p2_Won;
}

std::string War::talk(bool p1, bool p2) {
    if (p1) {
        return "Player 1 won this battle!";
    } else if (p2) {
        return "Player 2 won this battle!";
    } else {
        return "There is a tie.";
    }
}