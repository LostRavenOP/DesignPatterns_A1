#include "KeyCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>

// Constructor
KeyCard::KeyCard(int value)
    : Card(CardType::Key, value)
{
}

// String output
std::string KeyCard::str() const {
    return "Key(" + std::to_string(_value) + ")";
}

// Ability
void KeyCard::play(Game& game, Player& player) {
    //TODO: Implement ability
    // Place holder
    std::cout << "Key ability triggered!" << std::endl;

}

void KeyCard::willAddToBank(Game& game, Player& player) {
    //TODO: Implement functionality
}
