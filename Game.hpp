#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "Board.hpp"
#include "Pieces/Piece.hpp"
#include "Player.hpp"
#include <iostream>

class Game
{
public:
    Game(int width, int height) : x_size(width), y_size(height), currentPromotion(0, 0),
    m_window{sf::VideoMode(width, height), "Epic Chess Game"}, whitePlayer(Piece::Color::White), blackPlayer(Piece::Color::Black), 
    white_square{ sf::Vector2f(x_size / BoardSize, x_size / BoardSize)}, step_count(0),
        black_square{sf::Vector2f(x_size / BoardSize, x_size / BoardSize)}, state(0), step(Piece::Color::White), circle{float(15)}, current(0, 0){

        m_window.setFramerateLimit(200); 
        black_square.setFillColor( {81, 42, 42} );
        white_square.setFillColor( {124, 76, 62} );
        circle.setFillColor( {255, 255, 255, 30} );
        
        board.update_moves();


    }

    void Run();
    void HandleEvents();
    void Draw();
    void DrawSteps();
    void move(Point pos);
    void DrawPromotion(Point coord, Piece::Color color);
    void setCurrent(Point coord);
    void HandlePromotion(sf::Vector2i mouse_pos);

    void onCheckMate(Player player);
    void onStaleMate(Player player);

    void checkCheckMates();
    void checkStaleMates();
    void changeStep();


private:
    sf::RenderWindow m_window;
    int step_count;
    int x_size;
    int y_size;
    Board board;
    
    Player whitePlayer;
    Player blackPlayer;

    
    int state;
    Piece::Color step;
    Point current;
    Point currentPromotion;
    sf::Sprite sprites[4];

    sf::CircleShape circle;
    sf::RectangleShape white_square;
    sf::RectangleShape black_square;


};
