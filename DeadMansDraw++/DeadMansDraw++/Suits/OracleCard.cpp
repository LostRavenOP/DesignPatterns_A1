#include "OracleCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>

OracleCard::OracleCard(int value)
    : Card(CardType::Oracle, value)
{
}

std::string OracleCard::str() const {
    return "Oracle(" + std::to_string(_value) + ")";
}

// Ability: peek at the top card of the deck, then put it back.
// The player can then decide whether to draw again via the normal "Draw again?" prompt.
void OracleCard::play(Game& game, Player& player) {
    Card* peeked = game.drawCard();

    if (peeked == nullptr) {
        std::cout << "  The deck is empty. Nothing to peek at." << std::endl;
        return;
    }

    // Reveal the top card and immediately return it to the deck
    std::cout << "  The Oracle sees a " << peeked->str() << std::endl;
    game.returnToDeck(peeked);
}