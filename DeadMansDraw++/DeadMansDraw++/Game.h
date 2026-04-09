#ifndef GAME_H
#define GAME_H

#include "Card.h"
#include <vector>
#include <string>

class Player;

class Game {
public:
    Game();
    ~Game();

    // Initialises and runs the game loop
    void start();

    // Draws and returns the top card from the deck.
    // Returns nullptr if deck is empty.
    Card* drawCard();

    // Moves a card to the shared discard pile
    void discard(Card* card);

    // Moves all cards in a collection to the discard pile
    void discardAll(CardCollection& cards);

    // Returns the discard pile (read-only)
    const CardCollection& getDiscardPile() const;

    // Removes and returns the top card of the discard pile
    // (highest value of a given suit, for abilities that need it).
    // Returns nullptr if discard pile is empty.
    Card* drawFromDiscard();

	// Returns a card to the bottom of the deck (used for abilities that peek at the top card)
    void returnToDeck(Card* card);

    // Returns a pointer to the other player (not the current player)
    Player* getOtherPlayer() const;

    // Returns a pointer to the current player
    Player* getCurrentPlayer() const;

    // Returns current turn number (1-based, global across rounds)
    int getTurn() const;

    // Returns current round number (1-based)
    int getRound() const;

private:
    // Creates and shuffles the 54-card deck (9 suits x 6 values: 2-7,
    // except Mermaid which uses 4-9)
    void initialiseDeck();

    // Shuffles the deck in-place
    void shuffleDeck(CardCollection& cards);

    // Prints the game title ASCII art banner
    void printTitle() const;

    // Runs a single player's turn; returns true if the game should end
    bool runTurn();

    // Prints end-of-game results and declares the winner
    void printGameOver() const;

    CardCollection _deck;
    CardCollection _discardPile;

    Player* _players[2];
    int     _currentPlayerIndex;

    int _turn;    // global turn counter (each player's individual turn)
    int _round;   // round number (increments every 2 turns)

    static const int MAX_TURNS = 20;
};

#endif