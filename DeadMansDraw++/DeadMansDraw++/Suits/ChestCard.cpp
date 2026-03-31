#include "ChestCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>

// Constructor
ChestCard::ChestCard(int value)
    : Card(CardType::Chest, value)
{
}

// String output
std::string ChestCard::str() const {
    return "Chest(" + std::to_string(_value) + ")";
}

// Ability
void ChestCard::play(Game& game, Player& player) {
    //TODO: Implement ability
	// Place holder
    std::cout << "Chest ability triggered!" << std::endl;

}

void ChestCard::willAddToBank(Game& game, Player& player) {
	//TODO: Implement functionality
}
