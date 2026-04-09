#include "CannonCard.h"
#include "../Game.h"
#include "../Player.h"
#include <iostream>
#include <algorithm>
#include <map>

// Constructor
CannonCard::CannonCard(int value)
    : Card(CardType::Cannon, value) {
}

// String output
std::string CannonCard::str() const {
    return "Cannon(" + std::to_string(_value) + ")";
}

// Ability: discard the highest-value card of any suit from the other player's bank
void CannonCard::play(Game& game, Player& player) {
    Player* other = game.getOtherPlayer();
    const CardCollection& otherBank = other->getBank();

    if (otherBank.empty()) {
        std::cout << "  No cards in " << other->name() << "'s Bank. Play continues." << std::endl;
        return;
    }

    // Build a list of the highest-value card per suit currently in the other player's bank.
    // We use the same suit-grouping logic the spec describes for scoring.
    // Key: CardType, Value: pointer to the highest-value card of that suit
    std::map<CardType, Card*> topCards;
    for (Card* card : otherBank) {
        auto it = topCards.find(card->type());
        if (it == topCards.end() || card->value() > it->second->value()) {
            topCards[card->type()] = card;
        }
    }

    // Display the options to the current player
    std::cout << "  Discard the top card of any suit from " << other->name() << "'s Bank:" << std::endl;
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
    std::cout << "  " << player.name() << " discards " << target->str()
        << " from " << other->name() << "'s Bank." << std::endl;

    // Remove the chosen card from the other player's bank and send it to the discard pile
    other->removeFromBank(target);
    game.discard(target);
}