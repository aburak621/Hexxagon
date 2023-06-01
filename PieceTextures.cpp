
#include "PieceTextures.h"

sf::Texture PieceTextures::loadTexture(std::string str){
    sf::Texture tmp;
    if (!tmp.loadFromFile(str))
        std::cout << "Error loading file\n";
    return tmp;
}


sf::Texture PieceTextures::YellowPawn = PieceTextures::loadTexture("C:\\Users\\alior\\Desktop\\yellow.png");


sf::Texture PieceTextures::GreenPawn = PieceTextures::loadTexture("C:\\Users\\alior\\Desktop\\green.png");