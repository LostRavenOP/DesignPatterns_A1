#include "Player.h"
#include "Game.h"
#include "Card.h"
#include <iostream>
#include <vector>

Player::Player(std::string name) : _name(std::move(name)) {
}

Player::~Player() = default;

const std::string& Player::name() const
{
    return _name;
}

const CardCollection& Player::getPlayArea() const
{
    return _playArea;
}

const CardCollection& Player::getBank() const
{
    return _bank;
}

bool Player::playCard(Card* card, Game& game) {
	
	_playArea.push_back(card);

    std::cout << "Added card: " << card->str() << std::endl;
    std::cout << "Play area size: " << _playArea.size() << std::endl;

	if (isBust()) {
		std::cout << name() << " has busted!" << std::endl;
		return true;
	}

	card->play(game, *this);

	return false;
}

bool Player::isBust() const {

    for (int i = 0; i < _playArea.size(); i++)
    {
        for (int j = i + 1; j < _playArea.size(); j++)
        {
            if (_playArea[i]->type() == _playArea[j]->type())
            {
                return true;
            }
        }
    }
    return false;
}

