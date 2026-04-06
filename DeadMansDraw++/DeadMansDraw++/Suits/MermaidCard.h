#ifndef MERMAIDCARD_H
#define MERMAIDCARD_H

#include "../Card.h"

class MermaidCard : public Card {

    public:
        MermaidCard(int value);

        std::string str() const override;
        void play(Game& game, Player& player) override;
};

#endif