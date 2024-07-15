#include "Knight.hpp"

Knight::Knight(int coordX, int coordY, Color col) : Piece{coordX, coordY, col} {
    m_type = Type::Knight;
    if (m_color == Color::Black) {
        m_path = "../Piece_textures/b_knight_1x.png";
    }
    else {
        m_path = "../Piece_textures/w_knight_1x.png";
    }

    set_texture();
}

void Knight::set_texture() {
    if (!m_texture.loadFromFile(m_path)) {
        perror("Knight error: ");
    }
    m_sprite.setTexture(m_texture);
}

void Knight::getMoves(Board &board) {
    // std::vector<Point> result;
    moves = {};

    static Point possible_dirs[] = {
        {1, 2}, {2, 1}, {-1, 2}, {2, -1},
        {-1, -2}, {-2, -1}, {1, -2}, {-2, 1}
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

    // return result;
}

std::unique_ptr<Piece> Knight::clone() const {
    return std::make_unique<Knight>(*this);
}
