#include "board.h"
#include <cmath>

Board::Board(sf::RenderWindow &window) : window(window) {
}

void Board::initializeHexagonGrid() {
    std::vector<int> extraCells = {0, 1, 2, 3, 4, 3, 2, 1, 0};
    std::vector<int> cellOffsets = {0, 0, 0, 0, 0, 1, 2, 3, 4};
    for (int row = 0; row < 9; ++row) {
        int colNumber = 5 + extraCells[row];
        cells.emplace_back();
        for (int col = 0; col < colNumber; ++col) {
            float colOffset = col * HEX_WIDTH * 2 / 3.f + cellOffsets[row] * HEX_WIDTH * 2 / 3.f;
            float x = gridPosition.x + colOffset;
            float rowOffset = -(col + cellOffsets[row]) * HEX_HEIGHT / 2.f + row * HEX_HEIGHT;
            float y = gridPosition.y + rowOffset;

            if (row == 3 && col == 4 || row == 4 && col == 3 || row == 5 && col == 4) {
                cells[row].emplace_back(sf::Vector2f(x, y), HexType::none);
            } else if (row == 0 && col == 0 || row == 4 && col == 8 || row == 8 && col == 0) {
                cells[row].emplace_back(sf::Vector2f(x, y), HexType::playerOne);
            } else if (row == 0 && col == 4 || row == 4 && col == 0 || row == 8 && col == 4) {
                cells[row].emplace_back(sf::Vector2f(x, y), HexType::playerTwo);
            } else {
                cells[row].emplace_back(sf::Vector2f(x, y), HexType::empty);
            }
        }
    }
}

bool Board::placePiece(sf::Vector2i pieceIndex, sf::Vector2i placementIndex, int playerNo, bool adjacentMove) {
    
    return false;
}

void Board::drawHexagonGrid() {
    for (std::vector<Hexagon>& cols : cells) {
        for (Hexagon& cell : cols) {
            cell.draw(window);
        }
    }
}
