#include "ChestCard.h"
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

ChestCard::ChestCard(int value)
    : Card(CardType::Chest, value)
{
}

std::string ChestCard::str() const {
    return "Chest(" + std::to_string(_value) + ")";
}

// No immediate effect when drawn
void ChestCard::play(Game& game, Player& player) {
    std::cout << "        No immediate effect."
        << " If banked with a key, draw as many bonus cards"
        << " from the Discard pile as you moved into your Bank."
        << std::endl;
}

// Called just before this card is moved into the bank.
// Only acts if the play area still contains both a Chest and a Key.
void ChestCard::willAddToBank(Game& game, Player& player) {
    const CardCollection& playArea = player.getPlayArea();

	// No Key or Chest in the play area, no bonus cards drawn
    if (!hasChestAndKey(playArea)) {
        return;
    }

    // Count how many cards are about to be banked (the full play area)
    int bonusCount = static_cast<int>(playArea.size());

    std::cout << "        Chest and Key activated. Drawing " << bonusCount
        << " bonus card(s) from the Discard pile." << std::endl;

    int drawn = 0;
    for (int i = 0; i < bonusCount; i++) {
        Card* bonus = game.drawFromDiscard();
        if (bonus == nullptr) {
            break;
        }
        std::cout << "        Drew bonus card: " << bonus->str() << std::endl;
        // Route through playCard so bust-checking and any chained
        // willAddToBank calls are handled correctly
        player.playCard(bonus, game);
        drawn++;
    }

    if (drawn == 0) {
        std::cout << "        No cards drawn (Discard pile was empty)." << std::endl;
    }
}