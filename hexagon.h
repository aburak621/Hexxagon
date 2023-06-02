#include "common.h"

#define HEX_WIDTH 50
#define HEX_HEIGHT (HEX_WIDTH * 2 / 3.f)
#define RADIUS (HEX_HEIGHT * 0.9f)

class hexagon {
public:
    sf::Vector2f position;
    int type; // -1 = non-existent, 0 = empty, 1 = player1, 2 = player2
    
    hexagon(sf::Vector2f pos, int type);
    
    void draw(sf::RenderWindow& window);
};