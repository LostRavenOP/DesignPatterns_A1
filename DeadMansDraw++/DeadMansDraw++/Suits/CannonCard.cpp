#include "CannonCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>

// Constructor
CannonCard::CannonCard(int value)
    : Card(CardType::Cannon, value)
{
}

// String output
std::string CannonCard::str() const {
    return "Cannon(" + std::to_string(_value) + ")";
}

// Ability
void CannonCard::play(Game& game, Player& player) {
	//TODO: Implement ability
	// Place holder
    std::cout << "Cannon ability triggered!" << std::endl;

}