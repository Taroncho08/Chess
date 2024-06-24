#pragma once

#include "Piece.hpp"
#include "../Board.hpp"


class Board;
class Queen : public Piece {
public:
    Queen(int coordX, int coordY, Color col);

    void getMoves(Board &board) override;
    void set_texture();
};