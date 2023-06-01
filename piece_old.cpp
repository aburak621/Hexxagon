#include "piece_old.h"

const float Piece::HEX_WIDTH = 64.f;
const float Piece::HEX_HEIGHT = 64.f * 0.75f;
const sf::Vector2f Piece::gridPosition = sf::Vector2f(420.f, 32.f);

void Piece::setPiece(char type, bool player, int pos, bool moved) {
    setType(type);
    setPlayer(player);
    setPosition(pos);
    setMoved(moved);
}

std::string Piece::toString() {
    std::string str;

    str += m_player ? "Green " : "Yellow ";

    switch (m_type) {
        case 'P':
            str += "Pawn ";
            break;
        default:
            str += "??? ";
            break;
    }

    str += "\nto position\nX: ";
    str += std::to_string((m_position % 8) + 1);
    str += "  Y: ";
    str += std::to_string((m_position / 8) + 1);
    str += '\n';

    return str;
}

void Piece::move() {
    if (m_position <= -1 || 59 <= m_position) {
        m_position = -1;
        m_sprite.setColor(sf::Color(0x00000000));
        m_sprite.setPosition(sf::Vector2f((m_position % 9) * HEX_WIDTH + ((m_position / 9) % 2 == 1 ? HEX_WIDTH / 2.f : 0.f) + gridPosition.x,
                                          (m_position / 9) * (HEX_HEIGHT * 0.75f) + gridPosition.y));
        possibleMoves.clear();
        m_moved = true;
    }
    return;
}

void Piece::setTexture() {
    switch (m_type) {
        case 'P':
            m_texture = m_player ? PieceTextures::GreenPawn : PieceTextures::YellowPawn;
            break;
        default:
            std::cerr << "Error: Piece type does not exist.\n";
            break;
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2));
    m_sprite.setScale(sf::Vector2f(0.375f, 0.375f));
}
