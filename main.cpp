#include <SFML/Graphics.hpp>
#include "board.h"
#include <cmath>

#define RADIUS 20

void ClickCell(sf::Vector2f clickPos);

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Hexagon Window", sf::Style::Close);
    Board hexagonBoard(window);
    hexagonBoard.initializeHexagonGrid();

    std::vector<Piece> pieces = {Piece(sf::Vector2i(0, 0), true),
                                 Piece(sf::Vector2i(4, 8), true),
                                 Piece(sf::Vector2i(8, 0), true),
                                 Piece(sf::Vector2i(0, 4), false),
                                 Piece(sf::Vector2i(4, 0), false),
                                 Piece(sf::Vector2i(8, 4), false)};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        hexagonBoard.initializeHexagonGrid();

        for (Piece piece: pieces) {
            sf::CircleShape shape(RADIUS, 16);
            sf::Vector2f position(hexagonBoard.cells[piece.m_position.x][piece.m_position.y].m_position);
            position.x += hexagonBoard.HEX_WIDTH / 2 - RADIUS;
            position.y += hexagonBoard.HEX_HEIGHT / 2 - RADIUS;
            shape.setPosition(position);
            shape.setFillColor(piece.m_player ? sf::Color::Green : sf::Color::Red);
            window.draw(shape);
        }
        
        window.display();
    }

    return 0;
}

void ClickCell(sf::Vector2f clickPos, Board& board, bool& selected) {
    for (auto col: board.cells) {
        for (auto cell: col) {
            sf::Vector2f cellCenter(cell.m_position.x + board.HEX_WIDTH / 2, cell.m_position.y + board.HEX_HEIGHT / 2);
            float distance = sqrtf(powf(cellCenter.x - clickPos.x, 2) + powf(cellCenter.y - clickPos.y, 2));
            
            if (distance > RADIUS) { continue; }

            if (selected) {
                
            }
            else {
                if (cell.cellType == HexType::player) {
                    
                }
            }
        }
    }
}
