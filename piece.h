#ifndef PROJECT_PIECE_H
#define PROJECT_PIECE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Piece {
public:
    
    Piece(sf::Vector2<int> position, bool isPlayer) 
    {
        m_position = position;
        m_player = isPlayer;
    };

    sf::Vector2<int> m_position;
    bool m_player;
};

#endif //PROJECT_PIECE_H
