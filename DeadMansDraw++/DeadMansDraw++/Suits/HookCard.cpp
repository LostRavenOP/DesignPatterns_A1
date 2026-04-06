#include "HookCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>

// Constructor
HookCard::HookCard(int value)
    : Card(CardType::Hook, value)
{
}

// String output
std::string HookCard::str() const {
    return "Hook(" + std::to_string(_value) + ")";
}

// Ability
void HookCard::play(Game& game, Player& player) {
    //TODO: Implement ability
    // Place holder
    std::cout << "Hook ability triggered!" << std::endl;

}