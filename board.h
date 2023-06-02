#pragma once

#include "common.h"
#include "hexagon.h"

enum HexType {
    none = -1, empty, playerOne, playerTwo
};

class Board {
    // Every move a piece can make
    std::vector<sf::Vector2i> legalMoves = {
            {-2, -2},
            {-2, -1},
            {-2, 0},
            {-1, -2},
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0,  -2},
            {0,  -1},
            {0,  1},
            {0,  2},
            {1,  -1},
            {1,  0},
            {1,  1},
            {1,  2},
            {2,  0},
            {2,  1},
            {2,  2}
    };
    // Two tile moves a piece can make
    std::vector<sf::Vector2i> twoTileMoves = {
            {-2, -2},
            {-2, -1},
            {-2, 0},
            {-1, -2},
            {-1, 1},
            {0,  -2},
            {0,  2},
            {1,  -1},
            {1,  2},
            {2,  0},
            {2,  1},
            {2,  2}
    };
    // Relative coordinates of the adjacent tiles
    std::vector<sf::Vector2i> adjacentTiles = {
            {-1, -1},
            {-1, 0},
            {0,  -1},
            {0,  1},
            {1,  0},
            {1,  1},
    };
    sf::RenderWindow &window;
    sf::Vector2f gridPosition = sf::Vector2f((window.getSize().x - HEX_WIDTH * 6.333f) / 2.f,
                                             (window.getSize().y - HEX_HEIGHT * 4.f) / 2.f);
    int playerOneScore = 3;
    int playerTwoScore = 3;

    
public:
    std::vector<std::vector<Hexagon>> cells; // Every hexagon cell in a two-dimensional vector

    Board(sf::RenderWindow &window);

    void initializeHexagonGrid();
    void drawHexagonGrid();
    bool placePiece(sf::Vector2i pieceIndex, sf::Vector2i placementIndex, int playerNo);
    sf::Vector2i getIndexUnderCursor(sf::Vector2f mousePos);
    int convertAdjacentPieces(sf::Vector2i index, int playerNo);
    void printScores();
    bool isTherePossibleMove(int playerNo);
    void printGameOverMessage();
};