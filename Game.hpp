#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "Board.hpp"
#include "Pieces/Piece.hpp"

class Game
{
public:
    Game(int width, int height) : x_size(width), y_size(height),
    m_window{sf::VideoMode(width, height), "Epic Chess Game"},  white_square{sf::Vector2f(x_size / BoardSize, x_size / BoardSize)}, 
        black_square{sf::Vector2f(x_size / BoardSize, x_size / BoardSize)}, state(0), step(0), circle{float(10)}, current(0, 0){

        m_window.setFramerateLimit(200);  
        black_square.setFillColor( {81, 42, 42} );
        white_square.setFillColor( {124, 76, 62} );
        circle.setFillColor( {255, 255, 255, 30} );

        update_moves();


    }

    void Run();
    void HandleEvents();
    void Draw();
    void DrawSteps();
    void update_moves();

public:
    sf::RenderWindow m_window;
    int x_size;
    int y_size;
    Board board;

    bool state;

    //0 - white
    //1 - black
    bool step;
    Point current;

    sf::CircleShape circle;
    sf::RectangleShape white_square;
    sf::RectangleShape black_square;


};