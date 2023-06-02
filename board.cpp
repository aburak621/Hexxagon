#include "board.h"
#include <cmath>

Board::Board(sf::RenderWindow &window) : window(window) {
}

void Board::initializeHexagonGrid() {
    std::vector<int> extraCells = {0, 1, 2, 3, 4, 4, 4, 4, 4};
    for (int row = 0; row < 9; ++row) {
        int colNumber = 5 + extraCells[row];
        cells.emplace_back();
        for (int col = 0; col < colNumber; ++col) {
            float colOffset = col * HEX_WIDTH * 2 / 3.f;// + cellOffsets[row] * HEX_WIDTH * 2 / 3.f;
            float x = gridPosition.x + colOffset;
            float rowOffset = -(col + 0) * HEX_HEIGHT / 2.f + row * HEX_HEIGHT;
            float y = gridPosition.y + rowOffset;

            if (row == 3 && col == 4 || row == 4 && col == 3 || row == 5 && col == 5 ||
                row >= 5 && col + 5 - row <= 0) {
                cells[row].emplace_back(sf::Vector2f(x, y), HexType::none);
            } else if (row == 0 && col == 0 || row == 4 && col == 8 || row == 8 && col == 4) {
                cells[row].emplace_back(sf::Vector2f(x, y), HexType::playerOne);
            } else if (row == 0 && col == 4 || row == 4 && col == 0 || row == 8 && col == 8) {
                cells[row].emplace_back(sf::Vector2f(x, y), HexType::playerTwo);
            } else {
                cells[row].emplace_back(sf::Vector2f(x, y), HexType::empty);
            }
        }
    }
}

bool Board::placePiece(sf::Vector2i pieceIndex, sf::Vector2i placementIndex, int playerNo) {
    if (!(pieceIndex.x >= 0 && pieceIndex.x < cells.size()) &&
        !(pieceIndex.y >= 0 && pieceIndex.y < cells[pieceIndex.x].size())) { return false; }
    if (cells[pieceIndex.x][pieceIndex.y].type != playerNo) { return false; }
    // Check if move is valid
    for (auto &legalMove: legalMoves) {
        sf::Vector2i currentIndex(pieceIndex.x + legalMove.x, pieceIndex.y + legalMove.y);
        if (placementIndex == currentIndex && cells[currentIndex.x][currentIndex.y].type == HexType::empty) {
            cells[currentIndex.x][currentIndex.y].type = playerNo;

            // Check if it is a two tile move and delete the original piece if so
            for (auto &twoTileMove: twoTileMoves) {
                if (placementIndex.x == pieceIndex.x + twoTileMove.x &&
                    placementIndex.y == pieceIndex.y + twoTileMove.y) {
                    cells[pieceIndex.x][pieceIndex.y].type = HexType::empty;
                    break;
                }
            }
            // convert adjacent pieces function here
            convertAdjacentPieces(placementIndex, playerNo);
            return true;
        }
    }
    return false;
}

void Board::drawHexagonGrid() {
    for (std::vector<Hexagon> &cols: cells) {
        for (Hexagon &cell: cols) {
            cell.draw(window);
        }
    }
}

sf::Vector2i Board::getIndexUnderCursor(sf::Vector2f mousePos) {
    for (int row = 0; row < cells.size(); row++) {
        for (int col = 0; col < cells[row].size(); col++) {
            Hexagon cell = cells[row][col];
            float distance = sqrtf(
                    powf(mousePos.x - (cell.position.x + HEX_WIDTH / 2.f), 2) + powf(mousePos.y - cell.position.y, 2));
            if (distance <= RADIUS) {
                return {row, col};
            }
        }
    }
    return {-1, -1};
}

int Board::convertAdjacentPieces(sf::Vector2i index, int playerNo) {
    for (auto &tile: adjacentTiles) {
        int currentRow = index.x + tile.x;
        int currentCol = index.y + tile.y;
        if (!(currentRow >= 0 && currentRow < cells.size()) &&
            !(currentCol >= 0 && currentCol < cells[currentRow].size())) { continue; }
        Hexagon &currentTile = cells[currentRow][currentCol];
        if (currentTile.type == -1) { continue; }
        if (currentTile.type == (playerNo % 2) + 1) {
            currentTile.type = playerNo;
        }
    }
    return 0;
}
