#include "MermaidCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>

// Constructor
MermaidCard::MermaidCard(int value)
    : Card(CardType::Mermaid, value)
{
}

// String output
std::string MermaidCard::str() const {
    return "Mermaid(" + std::to_string(_value) + ")";
}

// Ability
void MermaidCard::play(Game& game, Player& player) {
    //TODO: Implement ability
    // Place holder
    std::cout << "Mermaid ability triggered!" << std::endl;

}