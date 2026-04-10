#include "OracleCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>

OracleCard::OracleCard(int value)
    : Card(CardType::Oracle, value) {
}

std::string OracleCard::str() const {
    return "Oracle(" + std::to_string(_value) + ")";
}

// Ability: peek at the top card of the deck, then choose whether to draw it.
void OracleCard::play(Game& game, Player& player) {

    // Peek — draw the card without committing it yet
    Card* peeked = game.drawCard();

    if (peeked == nullptr) {
        std::cout << "  The deck is empty. Nothing to peek at." << std::endl;
        return;
    }

    std::cout << "  The Oracle sees a " << peeked->str() << std::endl;

    // Ask the player if they want to take it
    std::string input;
    std::cout << "  Draw this card? (y/n): ";
    std::cin >> input;

    if (input == "y") {
        // Play it into the play area — handles bust-checking and ability
        player.playCard(peeked, game);
    }
    else {
        // Put it back on top of the deck
        game.returnToDeck(peeked);
        std::cout << "  " << player.name() << " returns the card to the deck."
            << std::endl;
    }
}