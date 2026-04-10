#include "KrakenCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>

KrakenCard::KrakenCard(int value)
    : Card(CardType::Kraken, value)
{
}

std::string KrakenCard::str() const {
    return "Kraken(" + std::to_string(_value) + ")";
}

// Ability: the player must draw and play 3 cards consecutively with no choice.
void KrakenCard::play(Game& game, Player& player) {
    const int FORCED_DRAWS = 3;

    std::cout << "  Draw " << FORCED_DRAWS
        << " cards from the deck and play each:" << std::endl;

    for (int i = 0; i < FORCED_DRAWS; i++) {
        if (game.getDeckSize() == 0) {
            std::cout << "  Deck is empty. Kraken draws end early." << std::endl;
            break;
        }

        Card* card = game.drawCard();
        std::cout << "  " << player.name() << " draws a " << card->str() << std::endl;

        // If the player busts mid-Kraken, stop drawing.
        bool busted = player.playCard(card, game);
        if (busted) {
            break;
        }
    }
}