#include "SwordCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>

// Constructor
SwordCard::SwordCard(int value)
    : Card(CardType::Sword, value)
{
}

// String output
std::string SwordCard::str() const {
    return "Sword(" + std::to_string(_value) + ")";
}

// Ability
void SwordCard::play(Game& game, Player& player) {
    //TODO: Implement ability
    // Place holder
    std::cout << "Sword ability triggered!" << std::endl;

}