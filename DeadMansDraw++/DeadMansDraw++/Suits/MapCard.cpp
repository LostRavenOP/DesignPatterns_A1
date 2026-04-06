#include "MapCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>

// Constructor
MapCard::MapCard(int value)
    : Card(CardType::Map, value)
{
}

// String output
std::string MapCard::str() const {
    return "Map(" + std::to_string(_value) + ")";
}

// Ability
void MapCard::play(Game& game, Player& player) {
    //TODO: Implement ability
    // Place holder
    std::cout << "Map ability triggered!" << std::endl;

}