#pragma once

#include "Point.hpp"
#include "Pieces/Piece.hpp"
#include "Board.hpp"

class Player {
public:
    Player(Piece::Color color);
    void setPoints(int val);
    int getPoints();

    Piece::Color getColor();
private:
    int m_points;
    Piece::Color m_color;


};
