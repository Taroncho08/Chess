#include "Rook.hpp"

Rook::Rook(int coordX, int coordY, Color col) : Piece{coordX, coordY, col} {
    if (m_color == Color::Black) {
        m_path = "../Piece_textures/b_rook_1x.png";
    }
    else {
        m_path = "../Piece_textures/w_rook_1x.png";
    }

    set_texture();
}

void Rook::set_texture() {
    if (!m_texture.loadFromFile(m_path)) {
        perror("Rook error: ");
    }
    m_sprite.setTexture(m_texture);
}

void Rook::getMoves(Board &board) {
    // std::vector<Point> result;
    moves = {};

    static Point possible_dirs[] = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}
    };

    for (auto move : possible_dirs) {
        auto candidate = move + Point(m_coordX, m_coordY);

        while (candidate.isValid())
        {
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

    // return result;
} 

void Rook::draw(sf::RenderWindow &window, int window_size) {
    m_sprite.setScale(0.14, 0.14);
    m_sprite.setPosition((window_size / BoardSize) * m_coordX + 7, (window_size / BoardSize) * m_coordY + 5);

    window.draw(m_sprite);
}