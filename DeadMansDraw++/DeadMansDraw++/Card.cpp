#include "Card.h"

// Constructor
Card::Card(CardType type, int value)
    : _type(type), _value(value)
{
}

// Return card type — return by value, matching the header declaration
CardType Card::type() const {
    return _type;
}

// Return card value
int Card::value() const {
    return _value;
}