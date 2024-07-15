#pragma once

#include "Piece.hpp"
#include "../Board.hpp"


class Board;
class Knight : public Piece {
public:
    Knight(int coordX, int coordY, Color col);
    void set_texture(); 
    void getMoves(Board &board) override;
    std::unique_ptr<Piece> clone() const override;
};
