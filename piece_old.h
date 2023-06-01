#ifndef _PIECE_H
#define _PIECE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "PieceTextures.h"

class Piece : public sf::Drawable {
public:
    Piece(char type = 'P', bool player = true, int pos = -1, bool moved = false)
            : m_type(type), m_player(player),
              m_position(pos), m_moved(moved),
              enPassant(-1),
              m_texture(),
              m_sprite(m_texture) {
        setTexture();
    }

    virtual void move() = 0;

    virtual void setTexture() = 0;

    virtual std::string toString() = 0;

    // Other member functions and variables...

protected:
    // Protected constructor to allow derived classes to access it
    Piece() = default;

    void setPiece(char type, bool player, int pos, bool moved = false);

    void setType(char ch) {
        m_type = ch;
        setTexture();
    }

    char getType() { return m_type; }

    void setPlayer(bool bl) {
        m_player = bl;
        setTexture();
    }

    bool getPlayer() { return m_player; }

    void setPosition(int pos) {
        m_position = pos;
        move();
    }

    int getPosition() { return m_position; }

    void setMoved(bool moved) { m_moved = moved; }

    bool getMoved() { return m_moved; }

    void setEnPassant(int x) { enPassant = x; }

    int getEnPassant() { return enPassant; }

    std::vector<int> &getPossibleMoves() { return possibleMoves; }
    // std::vector<int>& getDangerMoves(){return dangerMoves;} //domination move

private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    std::vector<int> possibleMoves;
    //std::vector<int> dangerMoves;

    static const float HEX_WIDTH;
    static const float HEX_HEIGHT;
    static const sf::Vector2f gridPosition;

    char m_type; //'P' = Pawn
    bool m_player; // true == Green , false == Yellow
    int m_position; // 0-58 board, -1 dead
    int enPassant;
    bool m_moved;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(m_sprite);
    }
};

#endif
