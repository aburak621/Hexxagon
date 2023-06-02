#include <unistd.h>
#include "common.h"
#include "board.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1280, 720)), "Hexagon Window", sf::Style::Default);
    sf::Font font;
    // There is a ../ because execution path is cmake-build-debug and the font file is one directory above, in the root
    if (!font.loadFromFile("../arial.ttf")) {
        // Error loading font
        return 1;
    }
    sf::Text text(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(0.f, 0.f));
    Board hexagonBoard(window, text);
    hexagonBoard.initializeHexagonGrid();
    sf::Vector2f mousePressPos;
    sf::Vector2f mouseReleasePos;
    bool turnPlayed = false; // If the current player played its turn
    int playersTurn = 1; // Which player's turn it is
    bool gameOver = false;
    bool aiEnabled = false;

    window.setFramerateLimit(60); // Limit the frame rate to 60fps

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        // Event loop
        while (window.pollEvent(event)) {
            // X button pressed
            if (event.type == sf::Event::Closed)
                window.close();

            // Keyboard inputs
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::A:
                        aiEnabled = !aiEnabled;
                        break;
                    case sf::Keyboard::R:
                        hexagonBoard.initializeHexagonGrid();
                        playersTurn = 1;
                        gameOver = false;
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    default:
                        break;
                }
            }

            // Mouse inputs
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
                    // Checks if player input is valid and places the piece if it is
                    if (pressIndex.x != -1 || releaseIndex.x != -1) {
                        turnPlayed = hexagonBoard.placePiece(pressIndex, releaseIndex, playersTurn);
                    }
                    // If the player played its turn, the turn switches to other player while checking for game over
                    if (turnPlayed) {
                        turnPlayed = false;
                        playersTurn = (playersTurn % 2) + 1;
                        gameOver = !hexagonBoard.isTherePossibleMove(playersTurn);
                    }
                }
            }
        }

        // Draw to the window
        window.clear(sf::Color::Black);
        hexagonBoard.drawHexagonGrid();
        hexagonBoard.printScores();
        if (gameOver) {
            hexagonBoard.printGameOverMessage();
        }
        std::string aiMode = aiEnabled ? "ON" : "OFF";
        text.setString("AI Mode: " + aiMode);
        text.setPosition({0, 60});
        window.draw(text);

        window.display();

        if (playersTurn == 2 && aiEnabled) {
            sleep(1);
            hexagonBoard.simulateAI();
            playersTurn = 1;
            gameOver = !hexagonBoard.isTherePossibleMove(playersTurn);
        }
    }

    return 0;
}
