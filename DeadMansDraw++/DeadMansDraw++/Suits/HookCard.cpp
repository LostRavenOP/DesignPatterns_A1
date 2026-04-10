#include "HookCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>
#include <map>
#include <vector>

HookCard::HookCard(int value)
    : Card(CardType::Hook, value) {
}

std::string HookCard::str() const {
    return "Hook(" + std::to_string(_value) + ")";
}

// Ability: play the highest-value card of any suit from your own bank
// back into your play area. You must select one card.
void HookCard::play(Game& game, Player& player) {
    const CardCollection& bank = player.getBank();

    if (bank.empty()) {
        std::cout << "        No cards in your Bank. Play continues." << std::endl;
        return;
    }

    // Find the highest-value card per suit in the current player's own bank
    std::map<CardType, Card*> topCards;
    for (Card* card : bank) {
        auto it = topCards.find(card->type());
        if (it == topCards.end() || card->value() > it->second->value()) {
            topCards[card->type()] = card;
        }
    }

    // Display options
    std::cout << "        Select a highest-value card from any of the suits in your Bank:"
        << std::endl;
    std::vector<std::pair<CardType, Card*>> options(topCards.begin(), topCards.end());
    for (int i = 0; i < static_cast<int>(options.size()); i++) {
        std::cout << "    (" << (i + 1) << ") " << options[i].second->str() << std::endl;
    }

    // Read a valid choice
    int choice = 0;
    while (choice < 1 || choice > static_cast<int>(options.size())) {
        std::cout << "        Which card do you pick? ";
        std::cin >> choice;
    }

    Card* target = options[choice - 1].second;
    std::cout << "        " << player.name() << " pulls "
        << target->str() << " from their Bank into their Play Area."
        << std::endl;

    // Remove from the player's own bank
    player.removeFromBank(target);

    // Play into the play area
    player.playCard(target, game);
}