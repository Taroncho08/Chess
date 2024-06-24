#include "King.hpp"

King::King(int coordX, int coordY, Color col) : Piece{coordX, coordY, col} {
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

            if (!board.isNull(y, x)) {
                if (board.getColor(x, y) != m_color) {
                    moves.push_back(candidate);
                }
                continue;
            }

            moves.push_back(candidate);
        }
    }

    // return result;
}