#pragma once

#include "Piece.hpp"
#include "../Board.hpp"

class Bishop : public Piece {
public:
    Bishop(int coordX, int coordY, Color col);
    
    void getMoves(Board& board) override;
    void set_texture() override;
    std::unique_ptr<Piece> clone() const override;
};
