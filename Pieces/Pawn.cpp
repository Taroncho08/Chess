#include "Pawn.hpp"
#include <iostream>

Pawn::Pawn(int coordX, int coordY, Color col) : Piece{coordX, coordY, col} {
    m_type = Type::Pawn;
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

    static Point eat_dirs[] = {
        {1, 1}, {-1, 1}
    };


    if (m_color == Piece::Color::Black) {
        for (auto move : possible_dirs) {
            auto candidate = move + Point(m_coordX, m_coordY);

            if (candidate.isValid()) {
                auto [x, y] = candidate.getCoords();

                if (!board.isNull(Point(x, y))) {
                    break;
                }
 
                moves.push_back(candidate);
                 
                if (m_coordY != 1) {
                    break;
                }

            }
            
            
        }

        for (auto move : eat_dirs) {
            auto candidate = move + Point(m_coordX, m_coordY);
            
            if (candidate.isValid()) {
                auto [x, y] = candidate.getCoords();

                if (!board.isNull(Point(x, y)) && board.getColor({x, y}) != m_color) {
                    moves.push_back(candidate);
                }
            }
        }
    }
    else if(m_color == Piece::Color::White) {
        for (auto move : possible_dirs) {
            auto candidate = Point(m_coordX, m_coordY) - move;

            if (candidate.isValid()) {
                auto [x, y] = candidate.getCoords();
                if (!board.isNull(Point(x, y))) {
                    break;
                }
                 
                moves.push_back(candidate);
            }

            if (m_coordY != 6) {
                break;
            }
            
        }
    }
    
        for (auto move : eat_dirs) {
            auto candidate = Point(m_coordX, m_coordY) - move;
            
            if (candidate.isValid()) {
                auto [x, y] = candidate.getCoords();

                if (!board.isNull(Point(x, y)) && board.getColor(Point(x, y)) != m_color) { 
                    moves.push_back(candidate);
                }
            }
        }

    // return result;
}

void Pawn::draw(sf::RenderWindow &window, int window_size) {
    m_sprite.setScale(0.20, 0.20);
    m_sprite.setPosition((window_size / BoardSize) * m_coordX + 20, (window_size / BoardSize) * m_coordY + 15);

    window.draw(m_sprite);
}

std::unique_ptr<Piece> Pawn::clone() const {
    return std::make_unique<Pawn>(*this);
}
