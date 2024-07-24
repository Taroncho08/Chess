#include "Piece.hpp"
#include "../Board.hpp"
#include "../Player.hpp"
#include <iostream>

Point Piece::getPosition() const {
    return Point(m_coordX, m_coordY);
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
    m_sprite.setScale(0.20, 0.20);
    m_sprite.setPosition((window_size / BoardSize) * m_coordX + 7, (window_size / BoardSize) * m_coordY + 7);

    window.draw(m_sprite);
}

void Piece::addMove(Point move) {
    if (move.isValid()) {
        moves.push_back(move);
    }
}


bool Piece::isLegalMove(Point move, Board& board) const {
    auto [x, y] = move.getCoords();
    Board tmp = board;
    tmp.setPosition(Point(m_coordX, m_coordY), move);
    //tmp.print();
    tmp.update_moves();
    
    if (tmp.isInCheck(Player(m_color))) {
        return false;
    }
    return true;
}

void Piece::move(Board& board, Point to) {
    board.setPosition({m_coordX, m_coordY}, {to});
    setPosition(to);
    board.update_moves();
}

bool Piece::isValidMove(Point point, Board& board) const {
    //auto vec = getMoves(board);
    if (point == Point(m_coordX, m_coordY)) {
        return false;
    }
    
    for (int i = 0; i < moves.size(); ++i) {

        if (point == moves[i] && isLegalMove(point, board)) {
            return true;
        }
    }
    return false;
}


const std::vector<Point> Piece::getMoveVector() const {
    return moves;
}

void Piece::setType(Type type) {
    m_type = type;
}

Piece::Type Piece::getType() const {
    return m_type;
}

bool Piece::canCaptureOpponentKing(Board& board, Player player) {
    for (auto i : moves) {
        
        if (!board.isNull(i)) {
            if (board.getType(i) == Piece::Type::King && board.getColor(i) == player.getColor()) {
                return true;
            }
        }
    }
    return false;
}
