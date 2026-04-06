#ifndef KRAKENCARD_H
#define KRAKENCARD_H

#include "../Card.h"

class KrakenCard : public Card {

public:
    KrakenCard(int value);

    std::string str() const override;
    void play(Game& game, Player& player) override;
};

#endif