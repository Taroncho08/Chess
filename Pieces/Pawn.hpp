#pragma once

#include "Piece.hpp"
#include "../Board.hpp"


class Board;
class Pawn : public Piece {
public:
    Pawn(int coordX, int coordY, Color col);
    void getMoves(Board &board) override;
    void draw(sf::RenderWindow &window, int window_size) override;
    void set_texture();
    std::unique_ptr<Piece> clone() const override;
};

