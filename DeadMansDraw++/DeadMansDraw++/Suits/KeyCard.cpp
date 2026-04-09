#include "KeyCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>

static bool hasChestAndKey(const CardCollection& playArea) {
    bool hasChest = false;
    bool hasKey = false;
    for (const Card* card : playArea) {
        if (card->type() == CardType::Chest) hasChest = true;
        if (card->type() == CardType::Key)   hasKey = true;
    }
    return hasChest && hasKey;
}

KeyCard::KeyCard(int value)
    : Card(CardType::Key, value)
{
}

std::string KeyCard::str() const {
    return "Key(" + std::to_string(_value) + ")";
}

// No immediate effect when drawn
void KeyCard::play(Game& game, Player& player) {
    std::cout << "  No immediate effect."
        << " If banked with a chest, draw as many bonus cards"
        << " from the Discard pile as you moved into your Bank."
        << std::endl;
}

// When both are present, ChestCard::willAddToBank handles the bonus draw.
// KeyCard::willAddToBank intentionally does nothing.
void KeyCard::willAddToBank(Game& game, Player& player) {
    // Deliberately empty — ChestCard owns the shared ability.
}