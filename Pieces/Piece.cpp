#include "Piece.hpp"

std::pair<int, int> Piece::getPosition() const {
    return std::make_pair(m_coordX, m_coordY);
}

void Piece::setColor(Piece::Color col) {
    m_color = col;
}

Piece::Color Piece::getColor() const {
    return m_color;
}

void Piece::setPosition(Point point) {
    const auto[x, y] = point.getCoords(); 

    m_coordX = x;
    m_coordY = y;
}
  

void Piece::draw(sf::RenderWindow &window, int window_size) {
    m_sprite.setScale(0.14, 0.14);
    m_sprite.setPosition((window_size / BoardSize) * m_coordX, (window_size / BoardSize) * m_coordY);

    window.draw(m_sprite);
}

bool Piece::isValidMove(Point point, Board& board) const {
    //auto vec = getMoves(board);
    if (point == Point(m_coordX, m_coordY)) {
        return false;
    }
    
    for (int i = 0; i < moves.size(); ++i) {
        if (point == moves[i]) {
            return true;
        }
    }
    return false;
}


const std::vector<Point>& Piece::getMoveVector() const {
    return moves;
}

