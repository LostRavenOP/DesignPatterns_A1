#include "KrakenCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>

// Constructor
KrakenCard::KrakenCard(int value)
    : Card(CardType::Kraken, value)
{
}

// String output
std::string KrakenCard::str() const {
    return "Kraken(" + std::to_string(_value) + ")";
}

// Ability
void KrakenCard::play(Game& game, Player& player) {
    //TODO: Implement ability
    // Place holder
    std::cout << "Kraken ability triggered!" << std::endl;

}