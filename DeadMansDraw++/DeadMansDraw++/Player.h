#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Card.h"

using CardCollection = std::vector<Card*>;

class Game;

class Player {
	public:
		Player(std::string name);

		~Player() = default;

		// Returns the player's name
		const std::string& name() const;

		// Returns the player's current hand of cards
		const CardCollection& getPlayArea() const;

		// Returns the player's current bank of cards
		const CardCollection& getBank() const;

		// Adds a card to the player's play area
		bool playCard(Card* card, Game& game);

		// Helper for adding play area to the player's bank
		void addToBank(Card* card);

		// Adds all cards from the play area to the bank, then clears the play area
		void bankPlayArea(Game& game);

		// Check if the player has busted
		bool isBust() const;

		// Clears the player's hand and bank
		void clearPlayArea();

		// Calculates the player's score based on the cards in their bank
		int calcScore() const;

		// Returns the player's current score (sum of card values in bank)
		int getScore() const;


	private:
		std::string _name;
		CardCollection _playArea;
		CardCollection _bank;
};

#endif