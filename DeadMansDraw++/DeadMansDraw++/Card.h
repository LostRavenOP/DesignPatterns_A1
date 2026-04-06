#include <string>
#include <vector>

class Game;
class Player;

// All possible card suits in the game
enum CardType{
    Cannon,
    Chest,
    Key,
    Anchor,
    Sword,
    Hook,
    Oracle,
    Map,
    Mermaid,
    Kraken
};

// Card collection type, used for the player's hand and bank
typedef std::vector<Card*> CardCollection;

// Abstract base class — every suit inherits from this
class Card {
    public:
        Card(CardType type, int value);
        virtual ~Card() = default;

        // Returns the card's suit enum
        const CardType& type() const;

        // Returns the card's point value
        int value() const;

        // Returns a display string
        virtual std::string str() const = 0;

        // Executes this card's ability. Called only when the player has NOT busted.
        virtual void play(Game& game, Player& player) = 0;

        // Called just before the card is moved into the player's bank.
        // Override in ChestCard and KeyCard only.
        virtual void willAddToBank(Game& game, Player& player) {}

    protected:
        CardType _type;
        int      _value;
};
