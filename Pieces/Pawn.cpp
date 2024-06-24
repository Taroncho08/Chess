#include "Pawn.hpp"
#include <iostream>

Pawn::Pawn(int coordX, int coordY, Color col) : Piece{coordX, coordY, col} {
    if (m_color == Color::Black) {
        m_path = "../Piece_textures/b_pawn_1x.png";
    }
    else {
        m_path = "../Piece_textures/w_pawn_1x.png";
    }

    set_texture();
}

void Pawn::set_texture() {
    if (!m_texture.loadFromFile(m_path)) {
        perror("Pawn error: ");
    }
    m_sprite.setTexture(m_texture);
}


void Pawn::getMoves(Board &board) {
    // std::vector<Point> result;
    moves = {};

    static Point possible_dirs[] = {
        {0, 1}, {0, 2}
    };

    if (m_color == Piece::Color::Black) {
        for (auto move : possible_dirs) {
            auto candidate = move + Point(m_coordX, m_coordY);

            if (candidate.isValid()) {
                auto [x, y] = candidate.getCoords();

                if (!board.isNull(y, x)) {
                    break;
                }
                moves.push_back(candidate);
                
                if (m_coordY != 1) {
                    break;
                }
            }
            
        }
    }
    else if(m_color == Piece::Color::White) {
        for (auto move : possible_dirs) {
            auto candidate = Point(m_coordX, m_coordY) - move;

            if (candidate.isValid()) {
                auto [x, y] = candidate.getCoords();
                if (!board.isNull(y, x)) {
                    break;
                }
                moves.push_back(candidate);
            }

            if (m_coordY != 6) {
                break;
            }
            
        }
    }

    // return result;
}

void Pawn::draw(sf::RenderWindow &window, int window_size) {
    m_sprite.setScale(0.14, 0.14);
    m_sprite.setPosition((window_size / BoardSize) * m_coordX + 10, (window_size / BoardSize) * m_coordY + 5);

    window.draw(m_sprite);
}