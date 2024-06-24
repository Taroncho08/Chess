#include "Game.hpp"
#include <iostream>


void Game::Run() {
    while (m_window.isOpen())
    {
        m_window.clear(sf::Color::Black);
        Draw();
        
        HandleEvents();
        m_window.display();
    }
}

void Game::Draw() {
    
    float rect_size = x_size / BoardSize;
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {

            if (i % 2 != 0) {
                if (j % 2 == 0) {   
                    black_square.setPosition(rect_size * j, rect_size * i);
                    m_window.draw(black_square);
                }
                else {
                    white_square.setPosition(rect_size * j, rect_size * i);
                    m_window.draw(white_square);
                }
            }
            else {
                if (j % 2 != 0) {
                    black_square.setPosition(rect_size * j, rect_size * i);
                    m_window.draw(black_square);
                }
                else {
                    white_square.setPosition(rect_size * j, rect_size * i);
                    m_window.draw(white_square);
                }
            }
        }

    }
    

    board.printPieces(m_window, x_size);
    DrawSteps();
    

}

void Game::DrawSteps() {
    if (state == 1) {
        auto [x, y] = current.getCoords();
        for (auto i : board.m_board[y][x]->getMoveVector()) {
            auto [x, y] = i.getCoords();
            int rect_size = x_size / BoardSize;
            circle.setPosition((x * rect_size) + rect_size / 3.f, (y *rect_size) + rect_size / 3.f);
            m_window.draw(circle);
        }
    }
}

void Game::HandleEvents() {
    sf::Event event;

    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {

                sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
                
                int mouseX = mousePosition.x / (x_size / BoardSize);
                int mouseY = mousePosition.y / (x_size / BoardSize);
                std::cout << mouseX << "  " << mouseY << std::endl;

                if (mouseX >= 0 && mouseX < x_size && mouseY >= 0 && mouseY < y_size) {

                    if (state == 1) {
                        auto [x, y] = current.getCoords(); 
                        if (board.m_board[y][x]->isValidMove({mouseX, mouseY}, board)) {

                            board.m_board[y][x]->setPosition( {mouseX, mouseY} );
                            board.m_board[mouseY][mouseX] = std::move(board.m_board[y][x]);
                            board.m_board[y][x] = nullptr;  
                            state = 0;
                            update_moves();
                            continue;
                        }
                    }

                    if (board.m_board[mouseY][mouseX] != nullptr) {
                        // auto res = board.m_board[mouseY][mouseX]->getMoves(board);
                        
                        if (board.m_board[mouseY][mouseX]->getMoveVector().size() > 0) {
                            std::cout << "fhf" << std::endl;
                            state = 1;
                            current = Point(mouseX, mouseY);
                        }
                        else {
                            state = 0;
                        }

                        auto mov = board.m_board[mouseY][mouseX]->getMoveVector();
                        for (auto i : mov) {
                            auto [x, y] = i.getCoords();

                            std::cout << "x: " << x << " y: " << y << std::endl;
                        }
                    }  
                    else {
                        state = 0;
                    } 
                }
            }
        }
    }
}

void Game::update_moves() {
    for (int i = 0; i < board.m_board.size(); ++i) {
        for (int j = 0; j < board.m_board.size(); ++j) {
            if (board.m_board[i][j] != nullptr) {
                board.m_board[i][j]->getMoves(board);
            }
        }
    }
}