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

#include "Player.hpp"



class Board {
public:    
    Board() : whiteCastle(true), blackCastle(true) {
        setupBoard();
    }

    
    Board(const Board& oth) : whiteCastle(oth.canWhiteCastle()), blackCastle(oth.canBlackCastle()) {
        m_board = oth.copy();
    }

    std::array<std::array<std::unique_ptr<Piece>, BoardSize>, BoardSize> copy() const; 
    //~Board();
    void setPosition(Point from, Point to);
    void printPieces(sf::RenderWindow &window, int wondow_size, int state, Point promotionCoords);
    void update_moves();
    bool isNull(Point pos);

    Piece::Color getColor(Point pos) const;
    Piece::Type getType(Point pos);

    bool hasValidMoves(Player player);
    bool isInCheck(Player player);
    bool isInCheckmate(Player player);
    bool isInStalemate(Player player);

    void addMoveToPiece(Point coord, Point move);
    bool canWhiteCastle() const;
    void setWhiteCastle(bool val);

    void setNull(Point pos);

    bool canBlackCastle() const;
    void setBlackCastle(bool val);

    void setCoords(Point point, Point coords);

    void print();

    
    friend class Game;
    
private:
    void setupBoard();
    void setupPiecesRow(int row, Piece::Color color, const std::vector<char>& pieceTypes);
    void setupEmpty();


private:
    std::array<std::array<std::unique_ptr<Piece>, BoardSize>, BoardSize> m_board;
    bool whiteCastle;
    bool blackCastle;

};
