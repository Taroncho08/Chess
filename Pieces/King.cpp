#include "King.hpp"
#include <iostream>

King::King(int coordX, int coordY, Color col) : Piece{coordX, coordY, col} {
    m_type = Type::King;
    if (m_color == Color::Black) {
        m_path = "../Piece_textures/b_king_1x.png";
    }
    else {
        m_path = "../Piece_textures/w_king_1x.png";
    }

    set_texture();
}

void King::set_texture() {
    if (!m_texture.loadFromFile(m_path))
        perror("King error: ");

    m_sprite.setTexture(m_texture);
}

bool King::isValidMove(Point point, Board& board) const {
    
    if (point == Point(m_coordX, m_coordY) + Point(2, 0)) {
        if (!board.isNull(Point(m_coordX, m_coordY) + Point(1, 0))) {
            return false;
        }

        if (m_color == Piece::Color::White) {
            if (!board.canWhiteCastle()) {
                return false;
            }
        }
        else {
            if (!board.canBlackCastle())
            {
                return false;
            }
        }
        if (isLegalMove(point, board)) {
            return true;
        }
        return false;
    }
    
    for (int i = 0; i < moves.size(); ++i) {

        if (point == moves[i] && isLegalMove(point, board)) {
            return true;
        }
    }
    return false;

}

void King::getMoves(Board &board) {
    // std::vector<Point> result;
    moves = {};

    static Point possible_dirs[] = {
        {0, 1}, {1, 0}, {1, 1}, {-1, 0},
        {0, -1}, {-1, -1}, {1, -1}, {-1, 1}
    };
    for (auto move : possible_dirs) {
        auto candidate = move + Point(m_coordX, m_coordY);
        
        if (candidate.isValid()) {
            auto [x, y] = candidate.getCoords();

            if (!board.isNull(Point(x, y))) {
                if (board.getColor({x, y}) != m_color) {   
                    moves.push_back(candidate);
                }
                continue;
            }
            
            moves.push_back(candidate);
            
        }
    }

    
    if (m_color == Piece::Color::White && board.canWhiteCastle() || m_color == Piece::Color::Black && board.canBlackCastle()) {
        auto candidate = Point(2, 0) + Point(m_coordX, m_coordY);
        auto[x, y] = candidate.getCoords();
        if (candidate.isValid()) {
            if (board.isNull(candidate)) {

                std::cout << "castle: " << x << " " << y << std::endl;
                moves.push_back(candidate);
            }
        }
    }

}

std::unique_ptr<Piece> King::clone() const {
    return std::make_unique<King>(*this);
}

void King::move(Board& board, Point to) {
    if (to == Point(m_coordX, m_coordY) + Point(2, 0)) {
        
        board.setPosition({m_coordX, m_coordY}, {to});
        setPosition(to);
        board.setPosition(to + Point{1, 0}, to - Point{1, 0});
        board.setCoords(to - Point{1, 0}, to - Point{1, 0});
        board.update_moves();
        
        return;
    }

    board.setPosition({m_coordX, m_coordY}, {to});
    setPosition(to);
    board.update_moves();

}
