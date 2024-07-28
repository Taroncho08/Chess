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

    
    if (board.canCastleToRight(m_color) && !board.isInCheck(m_color) && isLegalMove(Point(m_coordX, m_coordY) + Point(1, 0), board)) {
        auto candidate = Point(2, 0) + Point(m_coordX, m_coordY);
        if (candidate.isValid()) {
            if (board.isNull(candidate)) {

                moves.push_back(candidate);
            }
        }
    }
    else if (board.canCastleToLeft(m_color) && !board.isInCheck(m_color) && isLegalMove(Point(m_coordX, m_coordY) - Point(1, 0), board)) {
        auto candidate = Point(m_coordX, m_coordY) - Point(2, 0);
        if (candidate.isValid()) {
            if (board.isNull(candidate)) {

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
        Point new_rook_coord = to - Point(1, 0);
        Point cur_rook_coord = to + Point(1, 0);
        auto [n_x, n_y] = new_rook_coord.getCoords();
        auto [c_x, c_y] = cur_rook_coord.getCoords();

        board.setPosition(Point(c_x, c_y), Point(n_x, n_y));
        board.setCoords(Point(n_x, n_y), Point(n_x, n_y)); 

    }
    else if (to == Point(m_coordX, m_coordY) - Point(2, 0)) {
        Point new_rook_coord = to + Point(1, 0);
        Point cur_rook_coord = to - Point(2, 0);
        auto [n_x, n_y] = new_rook_coord.getCoords();
        auto [c_x, c_y] = cur_rook_coord.getCoords();

        board.setPosition(Point(c_x, c_y), Point(n_x, n_y));
        board.setCoords(Point(n_x, n_y), Point(n_x, n_y)); 

    }

    board.setPosition({m_coordX, m_coordY}, {to});
    setPosition(to);
    setMoved(true);
    board.update_moves();

}
