#include "hexagon.h"

hexagon::hexagon(sf::Vector2f pos, int type) : position(pos), type(type) {
}

void hexagon::draw(sf::RenderWindow& window) {
    sf::ConvexShape hexagon;
    hexagon.setPointCount(6);
    hexagon.setPoint(0, sf::Vector2f(HEX_WIDTH / 2.f, 0.f));
    hexagon.setPoint(1, sf::Vector2f(HEX_WIDTH / 3.f, -HEX_HEIGHT / 2.f));
    hexagon.setPoint(2, sf::Vector2f(HEX_WIDTH * 2 / 3.f, -HEX_HEIGHT / 2.f));
    hexagon.setPoint(3, sf::Vector2f(HEX_WIDTH, 0));
    hexagon.setPoint(4, sf::Vector2f(HEX_WIDTH * 2 / 3.f, HEX_HEIGHT / 2.f));
    hexagon.setPoint(5, sf::Vector2f(HEX_WIDTH / 3.f, HEX_HEIGHT / 2.f));

    hexagon.setFillColor(sf::Color::Blue);
    hexagon.setOutlineThickness(1.f);
    hexagon.setOutlineColor(sf::Color(0, 128, 0));
    
    hexagon.setPosition(position);
    window.draw(hexagon);

    if (type == 1 || type == 2) {
            sf::CircleShape shape(RADIUS, 16);
            shape.setPosition(sf::Vector2f(position.x + HEX_WIDTH / 2.f - RADIUS, position.y - RADIUS));
            shape.setFillColor(type == 1 ? sf::Color::Green : sf::Color::Red);
            window.draw(shape);
    }
}
