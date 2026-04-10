#include "MapCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>
#include <vector>

MapCard::MapCard(int value)
    : Card(CardType::Map, value) {
}

std::string MapCard::str() const {
    return "Map(" + std::to_string(_value) + ")";
}

// Ability: draw up to 3 cards from the discard pile, display them, then
// the player must pick exactly one to play into their play area.
// The unchosen cards are returned to the discard pile.
void MapCard::play(Game& game, Player& player) {
    const int DRAW_COUNT = 3;

    // Draw up to 3 cards from the discard pile
    std::vector<Card*> drawn;
    for (int i = 0; i < DRAW_COUNT; i++) {
        Card* card = game.drawFromDiscard();
        if (card == nullptr) {
            break;
        }
        drawn.push_back(card);
    }

    if (drawn.empty()) {
        std::cout << "  No cards in the discard. Play continues." << std::endl;
        return;
    }

    // Display the drawn options
    std::cout << "  Draw " << drawn.size()
        << " card(s) from the discard and pick one to add to the play area:"
        << std::endl;
    for (int i = 0; i < static_cast<int>(drawn.size()); i++) {
        std::cout << "  (" << (i + 1) << ") " << drawn[i]->str() << std::endl;
    }

    // Read a valid choice
    int choice = 0;
    while (choice < 1 || choice > static_cast<int>(drawn.size())) {
        std::cout << "  Which card do you pick? ";
        std::cin >> choice;
    }

    // Play the chosen card — handles bust-checking and its ability
    Card* chosen = drawn[choice - 1];
    player.playCard(chosen, game);

    // Return the unchosen cards to the discard pile
    for (int i = 0; i < static_cast<int>(drawn.size()); i++) {
        if (i != choice - 1) {
            game.discard(drawn[i]);
        }
    }
}