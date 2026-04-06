#include "OracleCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>

// Constructor
OracleCard::OracleCard(int value)
    : Card(CardType::Oracle, value)
{
}

// String output
std::string OracleCard::str() const {
    return "Oracle(" + std::to_string(_value) + ")";
}

// Ability
void OracleCard::play(Game& game, Player& player) {
    //TODO: Implement ability
    // Place holder
    std::cout << "Oracle ability triggered!" << std::endl;

}