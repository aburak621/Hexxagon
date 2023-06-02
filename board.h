#include "common.h"
#include "hexagon.h"

enum HexType { none = -1, empty, playerOne, playerTwo };
std::vector<sf::Vector2i> legalMoves = {
        sf::Vector2i(-2, 0),
        sf::Vector2i(-2, 1),
        sf::Vector2i(-2, 2),
        sf::Vector2i(-1, -1),
        sf::Vector2i(-1, 0),
        sf::Vector2i(-1, 1),
        sf::Vector2i(-1, 2),
        sf::Vector2i(0, -2),
        sf::Vector2i(0, -1),
        sf::Vector2i(0, 1),
        sf::Vector2i(0, 2),
        sf::Vector2i(1, -2),
        sf::Vector2i(1, -1),
        sf::Vector2i(1, 0),
        sf::Vector2i(1, 1),
        sf::Vector2i(2, 0),
        sf::Vector2i(2, -1),
        sf::Vector2i(2, -2),
};

class Board {
    sf::RenderWindow& window;
    sf::Vector2f gridPosition = sf::Vector2f(420.f, 420.f);

public:
    std::vector<std::vector<hexagon>> cells;
    
    Board(sf::RenderWindow& window); // Constructor
    void initializeHexagonGrid();
    bool placePiece(sf::Vector2i pieceIndex, sf::Vector2i placementIndex, int playerNo, bool adjacentMove);
};