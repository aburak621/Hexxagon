#include "common.h"
#include "board.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1280, 720)), "Hexagon Window", sf::Style::Default);
    Board hexagonBoard(window);
    hexagonBoard.initializeHexagonGrid();
    sf::Vector2f mousePressPos;
    sf::Vector2f mouseReleasePos;
    bool turnPlayed = false;
    int playersTurn = 1;
    bool gameOver = false;
    
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::R:
                        hexagonBoard.initializeHexagonGrid();
                        playersTurn = 1;
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    default:
                        break;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Pressed
                    mousePressPos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Released
                    mouseReleasePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    sf::Vector2i pressIndex = hexagonBoard.getIndexUnderCursor(mousePressPos);
                    sf::Vector2i releaseIndex = hexagonBoard.getIndexUnderCursor(mouseReleasePos);
                    if (pressIndex.x != -1 || releaseIndex.x != -1) {
                        turnPlayed = hexagonBoard.placePiece(pressIndex, releaseIndex, playersTurn);
                    }
                    if (turnPlayed) {
                        turnPlayed = false;
                        playersTurn = (playersTurn % 2) + 1;
                        gameOver = !hexagonBoard.isTherePossibleMove(playersTurn);
                        if (gameOver) {
                            hexagonBoard.printGameOverMessage();
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        hexagonBoard.drawHexagonGrid();


        window.display();
    }

    return 0;
}
