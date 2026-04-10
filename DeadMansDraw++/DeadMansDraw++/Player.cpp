#include "Player.h"
#include "Game.h"
#include "Card.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <algorithm>

Player::Player(std::string name) : _name(std::move(name)) {
}

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

void Player::printPlayArea() const {

    // Group cards by suit
    std::map<CardType, std::vector<Card*>> grouped;
    for (Card* card : _playArea) {
        grouped[card->type()].push_back(card);
    }

    // Print each suit group, sorted by value descending
    for (auto& pair : grouped) {
        std::vector<Card*>& cards = pair.second;
        std::sort(cards.begin(), cards.end(), [](Card* a, Card* b) {
            return a->value() > b->value();
            });
        std::cout << "        ";
        for (Card* card : cards) {
            std::cout << card->str() << " ";
        }
        std::cout << std::endl;
    }
}

void Player::printBank() const {
    std::map<CardType, std::vector<Card*>> grouped;
    for (Card* card : _bank) {
        grouped[card->type()].push_back(card);
    }
    for (auto& pair : grouped) {
        std::vector<Card*>& cards = pair.second;
        std::sort(cards.begin(), cards.end(), [](Card* a, Card* b) {
            return a->value() > b->value();
            });
        std::cout << "        ";
        for (Card* card : cards) {
            std::cout << card->str() << " ";
        }
        std::cout << std::endl;
    }
}

bool Player::playCard(Card* card, Game& game) {
    _playArea.push_back(card);

    // Bust check only — runTurn() is responsible for all bust output
    if (isBust()) {
        return true;
    }

    card->play(game, *this);

    return false;
}

bool Player::isBust() const {
    for (size_t i = 0; i < _playArea.size(); i++) {
        for (size_t j = i + 1; j < _playArea.size(); j++) {
            if (_playArea[i]->type() == _playArea[j]->type()) {
                return true;
            }
        }
    }
    return false;
}

void Player::addToBank(Card* card) {
    _bank.push_back(card);
}

void Player::removeFromBank(Card* card) {
    auto it = std::find(_bank.begin(), _bank.end(), card);
    if (it != _bank.end()) {
        _bank.erase(it);
    }
}

void Player::bankPlayArea(Game& game) {
    for (Card* card : _playArea) {
        card->willAddToBank(game, *this);
        addToBank(card);
    }
    clearPlayArea();
}

void Player::clearPlayArea() {
    _playArea.clear();
}

// Returns the sum of the highest value card in each suit in the bank
int Player::calcScore() const {
    std::map<CardType, int> topValues;
    for (const Card* card : _bank) {
        auto it = topValues.find(card->type());
        if (it == topValues.end() || card->value() > it->second) {
            topValues[card->type()] = card->value();
        }
    }
    int total = 0;
    for (auto& pair : topValues) {
        total += pair.second;
    }
    return total;
}