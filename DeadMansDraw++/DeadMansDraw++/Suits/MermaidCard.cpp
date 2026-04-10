#include "MermaidCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>

MermaidCard::MermaidCard(int value)
    : Card(CardType::Mermaid, value)
{
}

std::string MermaidCard::str() const {
    return "Mermaid(" + std::to_string(_value) + ")";
}

// No ability — Mermaids simply have higher point values (4–9 vs 2–7)
void MermaidCard::play(Game& game, Player& player) {
    std::cout << "        No effect but Mermaids are worth more." << std::endl;
}