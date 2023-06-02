#pragma once

#include "common.h"
#include "hexagon.h"

enum HexType {
    none = -1, empty, playerOne, playerTwo
};

class Board {
    std::vector<sf::Vector2i> legalMoves = {
            {-2, 0},
            {-2, 1},
            {-2, 2},
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {-1, 2},
            {0,  -2},
            {0,  -1},
            {0,  1},
            {0,  2},
            {1,  -2},
            {1,  -1},
            {1,  0},
            {1,  1},
            {2,  0},
            {2,  -1},
            {2,  -2}
    };
    sf::RenderWindow &window;
    sf::Vector2f gridPosition = sf::Vector2f((window.getSize().x - HEX_WIDTH * 6.333f) / 2.f,
                                             (window.getSize().y - HEX_HEIGHT * 4.f) / 2.f);

public:
    std::vector<std::vector<Hexagon>> cells;

    Board(sf::RenderWindow &window); // Constructor

    void initializeHexagonGrid();

    void drawHexagonGrid();

    bool placePiece(sf::Vector2i pieceIndex, sf::Vector2i placementIndex, int playerNo, bool adjacentMove);
};