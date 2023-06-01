#include "board.h"
#include <cmath>

Board::Board(sf::RenderWindow& window) : window(window) {
    gridPosition = sf::Vector2f(420.f, 32.f);
    HEX_SIZE = 50.f;
    HEX_HEIGHT = HEX_SIZE * 2.f;
    HEX_WIDTH = std::sqrt(3.f) / 3.f * HEX_HEIGHT;
}

void Board::drawHexagon(float x, float y, sf::Color fillColor, sf::Color outlineColor) {
    sf::ConvexShape hexagon;
    hexagon.setPointCount(6);
    hexagon.setPoint(0, sf::Vector2f(HEX_WIDTH / 2.f, 0.f));
    hexagon.setPoint(1, sf::Vector2f(HEX_WIDTH, HEX_HEIGHT / 4.f));
    hexagon.setPoint(2, sf::Vector2f(HEX_WIDTH, HEX_HEIGHT * 3.f / 4.f));
    hexagon.setPoint(3, sf::Vector2f(HEX_WIDTH / 2.f, HEX_HEIGHT));
    hexagon.setPoint(4, sf::Vector2f(0.f, HEX_HEIGHT * 3.f / 4.f));
    hexagon.setPoint(5, sf::Vector2f(0.f, HEX_HEIGHT / 4.f));

    hexagon.setFillColor(fillColor);
    hexagon.setOutlineThickness(1.f);
    hexagon.setOutlineColor(outlineColor);

    hexagon.setPosition(sf::Vector2f(x, y));

    window.draw(hexagon);
}

void Board::initializeHexagonGrid() {
    std::vector<int> extraCells = {0, 1, 2, 3, 4, 3, 2, 1, 0};
    std::vector<int> cellOffsets = {0, 1, 1, 2, 2, 2, 1, 1, 0};
    for (int row = 0; row < 9; ++row) {
        int colNumber = 5 + extraCells[row];
        cells.push_back(std::vector<Hexagon>());
        for (int col = 0; col < colNumber; ++col) {
            float x = gridPosition.x + col * HEX_WIDTH + ((row % 2 == 1) ? HEX_WIDTH / 2.f : 0.f) - HEX_WIDTH * cellOffsets[row];
            float y = gridPosition.y + row * (HEX_HEIGHT * 0.75f);
            
            if (row == 3 && col == 3 || row == 4 && col == 5 || row == 5 && col == 3) {
                cells[row].push_back(Hexagon(sf::Vector2f(x, y), HexType::empty));
                continue;
            }

            cells[row].push_back(Hexagon(sf::Vector2f(x, y)));

            sf::Color fillColor = sf::Color::Blue;
            sf::Color outlineColor = sf::Color::Black;

            drawHexagon(cells[row][col].m_position.x, cells[row][col].m_position.y, fillColor, outlineColor);
        }
    }
}
