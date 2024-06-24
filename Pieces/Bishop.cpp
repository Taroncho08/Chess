#include "Bishop.hpp"
#include <iostream>

Bishop::Bishop(int coordX, int coordY, Color col) : Piece{coordX, coordY, col} {
    if (m_color == Color::Black) {
        m_path = "../Piece_textures/b_bishop_1x.png";
    }
    else {
        m_path = "../Piece_textures/w_bishop_1x.png";
    }

    set_texture();
}

void Bishop::set_texture() {
    if (!m_texture.loadFromFile(m_path))
        perror("Bishop error: ");

    m_sprite.setTexture(m_texture);
}

void Bishop::getMoves(Board &board) {
    // std::vector<Point> result;
    moves = {};
    static Point possible_dirs[] = {
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    const auto initial = Point(m_coordX, m_coordY);

    bool flag = 0;
    for (auto move : possible_dirs) {
        auto candidate = initial + move;        

        while (candidate.isValid()) {
            auto [x, y] = candidate.getCoords();
            if (!board.isNull(y, x)) {
                if (board.getColor(x, y) != m_color) {
                    moves.push_back(candidate);
                }
                break;
            }

            moves.push_back(candidate);
            candidate += move;
        }
    }

} 