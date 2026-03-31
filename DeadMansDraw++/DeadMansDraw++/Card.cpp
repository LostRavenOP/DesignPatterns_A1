#include "Card.h"

// Constructor
Card::Card(CardType type, int value)
    : _type(type), _value(value)
{
}

// Destructor
Card::~Card() {
}

// Return card type
const CardType& Card::type() const {
    return _type;
}

// Return card value
int Card::value() const {
    return _value;
}

// Default behaviour (does nothing)
void Card::willAddToBank(Game& game, Player& player) {
}