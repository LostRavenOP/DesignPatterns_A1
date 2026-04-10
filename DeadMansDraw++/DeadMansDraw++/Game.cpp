#include "Game.h"
#include "Player.h"
#include "Card.h"

// Include all suit-specific card headers
#include "Suits/CannonCard.h"
#include "Suits/ChestCard.h"
#include "Suits/KeyCard.h"
#include "Suits/SwordCard.h"
#include "Suits/HookCard.h"
#include "Suits/OracleCard.h"
#include "Suits/MapCard.h"
#include "Suits/MermaidCard.h"
#include "Suits/KrakenCard.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <string>


Game::Game()
    : _currentPlayerIndex(0), _turn(1), _round(1)
{
	// Similar to deck shuffling, use a random number generator to pick two distinct player names
    std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(0, 9);

	// List of players to choose from
    std::string names[] = { "Sam", "Billy", "Jen", "Bob", "Sally",
                           "Joe", "Sue", "Sasha", "Tina", "Marge" };

    // Pick two distinct indices
    int i1 = dist(rng);
    int i2;
    do {
        i2 = dist(rng);
    } while (i2 == i1);

    _players[0] = new Player(names[i1]);
    _players[1] = new Player(names[i2]);
}

Game::~Game() {
    // Clean up players
    delete _players[0];
    delete _players[1];

    // Clean up remaining deck cards
    for (Card* card : _deck) {
        delete card;
    }

    // Clean up discard pile cards
    for (Card* card : _discardPile) {
        delete card;
    }
}

void Game::start() {
    printTitle();
    initialiseDeck();

    std::cout << "Starting Dead Man's Draw++!" << std::endl;

    // Game runs for MAX_TURNS total turns or until deck is empty
    while (_turn <= MAX_TURNS && !_deck.empty()) {
        if (runTurn()) {
            break;
        }
    }

    printGameOver();
}

Card* Game::drawCard() {
    if (_deck.empty()) {
        return nullptr;
    }
    Card* card = _deck.back();
    _deck.pop_back();
    return card;
}

void Game::discard(Card* card) {
    if (card != nullptr) {
        _discardPile.push_back(card);
    }
}

void Game::discardAll(CardCollection& cards) {
    for (Card* card : cards) {
        _discardPile.push_back(card);
    }
    cards.clear();
}

const CardCollection& Game::getDiscardPile() const {
    return _discardPile;
}

Card* Game::drawFromDiscard() {
    if (_discardPile.empty()) {
        return nullptr;
    }
    Card* card = _discardPile.back();
    _discardPile.pop_back();
    return card;
}

void Game::returnToDeck(Card* card) {
    if (card != nullptr) {
        _deck.push_back(card);
    }
}

int Game::getDeckSize() const {
    return static_cast<int>(_deck.size());
}

Player* Game::getCurrentPlayer() const {
    return _players[_currentPlayerIndex];
}

Player* Game::getOtherPlayer() const {
    return _players[1 - _currentPlayerIndex];
}

int Game::getTurn() const {
    return _turn;
}

int Game::getRound() const {
    return _round;
}

void Game::initialiseDeck() {
    // Standard suits: values 2–7 (6 cards each)
    int standardValues[] = { 2, 3, 4, 5, 6, 7 };

    for (int v : standardValues) {
        _deck.push_back(new CannonCard(v));
        _deck.push_back(new ChestCard(v));
        _deck.push_back(new KeyCard(v));
        _deck.push_back(new SwordCard(v));
        _deck.push_back(new HookCard(v));
        _deck.push_back(new OracleCard(v));
        _deck.push_back(new MapCard(v));
        _deck.push_back(new KrakenCard(v));
    }

    // Mermaid: values 4–9 (higher point value per spec)
    int mermaidValues[] = { 4, 5, 6, 7, 8, 9 };
    for (int v : mermaidValues) {
        _deck.push_back(new MermaidCard(v));
    }

    // Total: 8 suits x 6 cards + 6 mermaid = 54 cards
    shuffleDeck(_deck);
}

void Game::shuffleDeck(CardCollection& cards) {
    CardCollection temp{ cards.begin(), cards.end() };
    std::shuffle(temp.begin(), temp.end(),
        std::mt19937{ std::random_device{}() });
    std::copy(temp.begin(), temp.end(), cards.begin());
}

void Game::printTitle() const {
    std::cout << R"(
______                  _   ___  ___              _
|  _  \                | |  |  \/  |             ( )
| | | | ___   __ _   __| |  | .  . |  __ _  _ __ |/ ___
| | | |/ _ \ / _` | / _` |  | |\/| | / _` || '_ \  / __|
| |/ /|  __/| (_| || (_| |  | |  | || (_| || | | | \__ \
______ \___| \__,_| \__,_|  \_|  |_/ \__,_||_| |_| |___/
|  _  \                         _      _
| | | | _ __  __ _ __      __ _| |_  _| |_
| | | || '__|/ _` |\ \ /\ / /|_   _||_   _|
| |/ / | |  | (_| | \ V  V /   |_|    |_|
|___/  |_|   \__,_|  \_/\_/      
    )" << std::endl;
}

bool Game::runTurn() {
    Player* current = getCurrentPlayer();

    // Print round/turn header
    std::cout << "--- Round " << _round << ", Turn " << _turn << " ---" << std::endl;
    std::cout << current->name() << "'s turn." << std::endl;

    // Print current player's bank
    std::cout << current->name() << "'s Bank:" << std::endl;
    current->printBank();
    std::cout << "| Score: " << current->calcScore() << std::endl;

    bool playerBusted = false;

    // Player draws at least one card per turn
    while (true) {
        // Check if deck is empty
        if (_deck.empty()) {
            std::cout << "Deck is empty. Game over." << std::endl;
            return true; // signal game end
        }

        // Draw a card
        Card* card = drawCard();
        std::cout << current->name() << " draws a " << card->str() << std::endl;

        // playCard adds to play area, checks bust, calls ability if not bust
        bool busted = current->playCard(card, *this);

        if (busted) {
            // Move all play area cards to the discard pile
            CardCollection& playArea = const_cast<CardCollection&>(current->getPlayArea());
            discardAll(playArea);
            current->clearPlayArea();
            playerBusted = true;
            break;
        }

        // Print play area
        std::cout << current->name() << "'s Play Area:" << std::endl;
        current->printPlayArea();

        // Ask if the player wants to draw again
        std::cout << "Draw again? (y/n): ";
        std::string input;
        std::cin >> input;

        if (input != "y") {
            // Bank all play area cards
            current->bankPlayArea(*this);
            break;
        }
    }

    // Advance turn and round counters
    _turn++;
    if (_turn % 2 == 1) {
        // Both players have gone — new round
        _round++;
    }

    // Switch to the other player
    _currentPlayerIndex = 1 - _currentPlayerIndex;

    return false; // game continues
}

void Game::printGameOver() const {
    std::cout << "--- Game Over ---" << std::endl;

    for (int i = 0; i < 2; i++) {
        std::cout << _players[i]->name() << "'s Bank:" << std::endl;
        _players[i]->printBank();
        std::cout << "| Score: " << _players[i]->calcScore() << std::endl;
    }

    int score0 = _players[0]->calcScore();
    int score1 = _players[1]->calcScore();

    if (score0 > score1) {
        std::cout << _players[0]->name() << " wins!" << std::endl;
    }
    else if (score1 > score0) {
        std::cout << _players[1]->name() << " wins!" << std::endl;
    }
    else {
        std::cout << "It's a tie!" << std::endl;
    }
}