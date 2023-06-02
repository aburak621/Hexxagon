#include "common.h"
#include "board.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1280, 720)), "Hexagon Window", sf::Style::Default);
    Board hexagonBoard(window);
    hexagonBoard.initializeHexagonGrid();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        hexagonBoard.drawHexagonGrid();

        
        window.display();
    }

    return 0;
}
