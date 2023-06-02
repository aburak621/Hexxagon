#include "board.h"
#include <cmath>
#include <random>

Board::Board(sf::RenderWindow &window) : window(window) {
}

// Initializes the Hexagonal board with the default piece placements.
void Board::initializeHexagonGrid() {
    std::srand(std::time(nullptr));
    playerOneScore = 3;
    playerTwoScore = 3;
    cells.clear();
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

// Check if the piece in the first index is able to be placed in the placement index.
// Returns true is placement has taken place, false otherwise.
bool Board::placePiece(sf::Vector2i pieceIndex, sf::Vector2i placementIndex, int playerNo) {
    if (!(pieceIndex.x >= 0 && pieceIndex.x < cells.size()) &&
        !(pieceIndex.y >= 0 && pieceIndex.y < cells[pieceIndex.x].size())) { return false; }
    if (cells[pieceIndex.x][pieceIndex.y].type != playerNo) { return false; }
    // Check if move is valid
    for (auto &legalMove: legalMoves) {
        sf::Vector2i currentIndex(pieceIndex.x + legalMove.x, pieceIndex.y + legalMove.y);

        if (!(currentIndex.x >= 0 && currentIndex.x < cells.size()) ||
            !(currentIndex.y >= 0 && currentIndex.y < cells[currentIndex.x].size())) { continue; }
        if (placementIndex == currentIndex && cells[currentIndex.x][currentIndex.y].type == HexType::empty) {
            cells[currentIndex.x][currentIndex.y].type = playerNo;

            // Check if it is a two tile move and delete the original piece if so
            for (auto &twoTileMove: twoTileMoves) {
                if (placementIndex.x == pieceIndex.x + twoTileMove.x &&
                    placementIndex.y == pieceIndex.y + twoTileMove.y) {
                    cells[pieceIndex.x][pieceIndex.y].type = HexType::empty;
                    if (playerNo == 1) {
                        playerOneScore--;
                    } else if (playerNo == 2) {
                        playerTwoScore--;
                    }
                    break;
                }
            }

            // Convert adjacent pieces
            int convertedCount = convertAdjacentPieces(placementIndex, playerNo);
            // Update scores
            if (playerNo == 1) {
                playerOneScore++;
                playerOneScore += convertedCount;
                playerTwoScore -= convertedCount;
            } else if (playerNo == 2) {
                playerTwoScore++;
                playerOneScore -= convertedCount;
                playerTwoScore += convertedCount;
            }
            printScores();
            return true;
        }
    }
    return false;
}

// Draws every Hexagon.
void Board::drawHexagonGrid() {
    for (std::vector<Hexagon> &cols: cells) {
        for (Hexagon &cell: cols) {
            cell.draw(window);
        }
    }
}

// Gets the index of the Hexagon under the cursor in the cells vectors.
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

// Converts the pieces around given index to the pieces of the given player.
int Board::convertAdjacentPieces(sf::Vector2i index, int playerNo) {
    int convertedCount = 0;
    for (auto &tile: adjacentTiles) {
        int currentRow = index.x + tile.x;
        int currentCol = index.y + tile.y;
        if (!(currentRow >= 0 && currentRow < cells.size()) ||
            !(currentCol >= 0 && currentCol < cells[currentRow].size())) { continue; }
        Hexagon &currentTile = cells[currentRow][currentCol];
        if (currentTile.type == -1) { continue; }
        if (currentTile.type == (playerNo % 2) + 1) {
            currentTile.type = playerNo;
            convertedCount++;
        }
    }
    return convertedCount;
}

// Prints the scores.
void Board::printScores() {
    std::cout << "Player 1: " << playerOneScore << " Player 2: " << playerTwoScore << std::endl;
}

// Check if there is any move possible for the given player.
bool Board::isTherePossibleMove(int playerNo) {
    for (int row = 0; row < cells.size(); row++) {
        for (int col = 0; col < cells[row].size(); col++) {
            Hexagon &cell = cells[row][col];
            if (cell.type != playerNo) { continue; }
            for (auto &tile: legalMoves) {
                int currentRow = row + tile.x;
                int currentCol = col + tile.y;
                if (!(currentRow >= 0 && currentRow < cells.size()) ||
                    !(currentCol >= 0 && currentCol < cells[currentRow].size())) { continue; }
                if (cells[currentRow][currentCol].type == HexType::empty) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Prints which player won the game and prompts for restarting the game.
void Board::printGameOverMessage() {
    bool playerOneWon = playerOneScore > playerTwoScore;
    std::cout << "Player " << (playerOneWon ? "1" : "2") << " won the game!" << std::endl;
    std::cout << "Press 'R' to restart the game." << std::endl;
}

void Board::simulateAI() {
    sf::Vector2i optimumPieceIndex(-1, -1);
    sf::Vector2i optimumMove(0, 0);
    int maxConversionCount = 0;
    bool foundAMove = false;
    for (int row = 0; row < cells.size(); row++) {
        for (int col = 0; col < cells[row].size(); col++) {
            Hexagon &cell = cells[row][col];
            if (cell.type != 2) { continue; }
            for (auto &tile: legalMoves) {
                int currentRow = row + tile.x;
                int currentCol = col + tile.y;
                if (!(currentRow >= 0 && currentRow < cells.size()) ||
                    !(currentCol >= 0 && currentCol < cells[currentRow].size())) { continue; }
                if (cells[currentRow][currentCol].type == HexType::empty) {
                    int conversionCount = countAdjacentEnemyPieces(sf::Vector2i(currentRow, currentCol), 2);
                    if (conversionCount > maxConversionCount) {
                        maxConversionCount = conversionCount;
                        optimumPieceIndex = sf::Vector2i(row, col);
                        optimumMove = tile;
                        foundAMove = true;
                    }
                    bool shouldChangeMove = (std::rand() % 100) <= 20;
                    if (maxConversionCount == 0 && shouldChangeMove || !foundAMove) {
                        optimumPieceIndex = sf::Vector2i(row, col);
                        optimumMove = tile;
                        foundAMove = true;
                    }
                }
            }
        }
    }
    placePiece(optimumPieceIndex, optimumPieceIndex + optimumMove, 2);
}

int Board::countAdjacentEnemyPieces(sf::Vector2i index, int playerNo) {
    int convertedCount = 0;
    for (auto tile: adjacentTiles) {
        int currentRow = index.x + tile.x;
        int currentCol = index.y + tile.y;
        if (!(currentRow >= 0 && currentRow < cells.size()) ||
            !(currentCol >= 0 && currentCol < cells[currentRow].size())) { continue; }
        Hexagon currentTile = cells[currentRow][currentCol];
        if (currentTile.type == -1) { continue; }
        if (currentTile.type == (playerNo % 2) + 1) {
            currentTile.type = playerNo;
            convertedCount++;
        }
    }
    return convertedCount;
}
