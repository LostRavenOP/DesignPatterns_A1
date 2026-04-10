#include "SwordCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>
#include <map>
#include <vector>

SwordCard::SwordCard(int value)
    : Card(CardType::Sword, value) {
}

std::string SwordCard::str() const {
    return "Sword(" + std::to_string(_value) + ")";
}

// Ability: steal the highest-value card of any suit from the other player's
// bank into your play area. You must select one card.
void SwordCard::play(Game& game, Player& player) {
    Player* other = game.getOtherPlayer();
    const CardCollection& otherBank = other->getBank();

    if (otherBank.empty()) {
        std::cout << "  No cards in " << other->name()
            << "'s Bank. Play continues." << std::endl;
        return;
    }

    // Find the highest-value card per suit in the other player's bank
    std::map<CardType, Card*> topCards;
    for (Card* card : otherBank) {
        auto it = topCards.find(card->type());
        if (it == topCards.end() || card->value() > it->second->value()) {
            topCards[card->type()] = card;
        }
    }

    // Display options
    std::cout << "  Steal the top card of any suit from "
        << other->name() << "'s Bank into your Play Area:" << std::endl;
    std::vector<std::pair<CardType, Card*>> options(topCards.begin(), topCards.end());
    for (int i = 0; i < static_cast<int>(options.size()); i++) {
        std::cout << "  (" << (i + 1) << ") " << options[i].second->str() << std::endl;
    }

    // Read a valid choice
    int choice = 0;
    while (choice < 1 || choice > static_cast<int>(options.size())) {
        std::cout << "  Which card do you pick? ";
        std::cin >> choice;
    }

    Card* target = options[choice - 1].second;
    std::cout << "  " << player.name() << " steals "
        << target->str() << " from " << other->name() << "'s Bank."
        << std::endl;

    // Remove from the other player's bank
    other->removeFromBank(target);

    // Play into the current player's play area
    player.playCard(target, game);
}