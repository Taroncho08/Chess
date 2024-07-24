#pragma once

#include <utility>
#include <vector>
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>
//#include "../Player.hpp"
#include "../Constants.hpp"
#include "../Point.hpp"
// #include "../Board.hpp"

class Player;
class Board;
class Piece {
public:
    enum class Color { White, Black };
    enum class Type { Bishop, King, Knight, Pawn, Queen, Rook };

public:
    Piece() : m_coordX(-1), m_coordY(-1), m_color(Color::White) {}
    Piece(int coordX, int coordY, Color col) 
        : m_coordX { coordX }
        , m_coordY { coordY }
        , m_color  { col }
    {}

    virtual void draw(sf::RenderWindow &window, int window_size);
    virtual void getMoves(Board& board) = 0;
    virtual std::unique_ptr<Piece> clone() const = 0;
    virtual bool isValidMove(Point move, Board& board) const;

    bool isLegalMove(Point move, Board& board) const;
    void addMove(Point move);

    virtual void move(Board& board, Point to); 
    virtual void set_texture() = 0;
    virtual bool canCaptureOpponentKing(Board &board, Player player);

    void setPosition(Point point);
    Point getPosition() const;

    void setColor(Color col);
    Color getColor() const;

    const std::vector<Point> getMoveVector() const;

    Type getType() const;
    void setType(Type type);

protected:
    std::string m_path;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    int m_coordX;
    int m_coordY;
    Color m_color;
    Type m_type;

    std::vector<Point> moves;

};

