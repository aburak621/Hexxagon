

#ifndef PROJECT_PIECETEXTURES_H
#define PROJECT_PIECETEXTURES_H


#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class PieceTextures{
public:

    static sf::Texture YellowPawn;


    static sf::Texture GreenPawn;

    static sf::Texture loadTexture(std::string str);
};

#endif