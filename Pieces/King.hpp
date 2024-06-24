#pragma once

#include "Piece.hpp"
#include "../Board.hpp"

class Board;
class King : public Piece {
public:
    King(int coordX, int coordY, Color col);
    void getMoves(Board &board) override;
    void set_texture() override;

};