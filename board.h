

#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "piece.h"

enum HexType { empty, player, enemy };

class Hexagon {
public:
    Hexagon(sf::Vector2f position, HexType type= HexType::empty) {
        m_position = position;
        cellType = type;
    }
    sf::Vector2f m_position;
    HexType cellType;
    Piece* currentPiece = nullptr;
};

class Board {
private:
    sf::RenderWindow& window;
    sf::Vector2f gridPosition;

    void drawHexagon(float x, float y, sf::Color fillColor, sf::Color outlineColor);

public:
    float HEX_SIZE;
    float HEX_HEIGHT;
    float HEX_WIDTH;
    std::vector<std::vector<Hexagon>> cells;
    Board(sf::RenderWindow& window); // Constructor
    void initializeHexagonGrid();
};


#endif