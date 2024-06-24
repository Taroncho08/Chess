#pragma once

#include <memory>
#include <array>
#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Pieces/Piece.hpp"
#include "Pieces/Bishop.hpp"
#include "Pieces/Rook.hpp"
#include "Pieces/King.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Queen.hpp"



class Board {
public:    
    Board();
    //~Board();
    void setPositions();
    void printPieces(sf::RenderWindow &window, int wondow_size);
    bool isNull(int x, int y);
    Piece::Color getColor(int x, int y);
    
    friend class Game;
    
private:
    void setupBoard();
    void setupPiecesRow(int row, Piece::Color color, const std::vector<char>& pieceTypes);
    void setupEmpty();


private:
    std::array<std::array<std::unique_ptr<Piece>, BoardSize>, BoardSize> m_board;

};