#ifndef MAPCARD_H
#define MAPCARD_H

#include "../Card.h"

class MapCard : public Card {
public:
    MapCard(int value);

    std::string str() const override;
    void play(Game& game, Player& player) override;
};

#endif