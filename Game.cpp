#include "Game.hpp"
#include "Constants.hpp"
#include "Pieces/Piece.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>


void Game::Run() {
    while (m_window.isOpen())
    {
        m_window.clear(sf::Color::Black);
                
        HandleEvents();
        Draw();

        m_window.display();

        
    }
}

void Game::Draw() {
    
    float rect_size = x_size / BoardSize;
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (state == 1 && Point(j, i) == current) {
                black_square.setFillColor( {145, 106, 38} );
                white_square.setFillColor( {145, 106, 38} );
            }
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
            if (state == 1) {
                black_square.setFillColor( {81, 42, 42} );
                white_square.setFillColor( {124, 76, 62} );
            }

        }

    }
    

    board.printPieces(m_window, x_size, state, currentPromotion);
    if (state == 1) {
        DrawSteps();
    }
    else if (state == 2) {
        DrawPromotion(currentPromotion, board.getColor(currentPromotion));
    }

}

void Game::DrawSteps() {
    if (state == 1) {
        auto [x, y] = current.getCoords();
        for (auto i : board.m_board[y][x]->getMoveVector()) {
            if (board.m_board[y][x]->isValidMove(i, board)) {
                auto [x, y] = i.getCoords();
                int rect_size = x_size / BoardSize;
                circle.setPosition((x * rect_size) + rect_size / 3.f, (y * rect_size) + rect_size / 3.f);
                m_window.draw(circle);
            }
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
            if (state == 2) {
                HandlePromotion(sf::Mouse::getPosition(m_window));
                return;
            }
            if (event.mouseButton.button == sf::Mouse::Left) {

                sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
                
                int mouseX = mousePosition.x / (x_size / BoardSize);
                int mouseY = mousePosition.y / (x_size / BoardSize);
                std::cout << mouseX << "  " << mouseY << std::endl;

                move(Point(mouseX, mouseY));                
            }
        }
    }
}

void Game::HandlePromotion(sf::Vector2i mouse_pos) {
    auto [x, y] = current.getCoords();
    auto x_coord = mouse_pos.x / (x_size / BoardSize);
    auto y_coord = mouse_pos.y / (x_size / BoardSize);

    bool flag = 0;
    auto translated_pos = m_window.mapPixelToCoords(mouse_pos);
    for (int i = 0; i < 4; ++i) {
        std::cout << "for" << std::endl;
        if(sprites[i].getGlobalBounds().contains(translated_pos)) {
            std::cout << "saasdas" << std::endl;
             switch (i) {
                case 0:
                    board.m_board[y_coord][x_coord] = std::make_unique<Bishop>(x_coord, y_coord, board.getColor(currentPromotion));
                    flag = 1;
                    break;
                case 1:
                    board.m_board[y_coord][x_coord] = std::make_unique<Knight>(x_coord, y_coord, board.getColor(currentPromotion));
                    flag = 1;
                    break;
                case 2:
                    board.m_board[y_coord][x_coord] = std::make_unique<Queen>(x_coord, y_coord, board.getColor(currentPromotion));
                    flag = 1;
                    break;
                case 3:
                    board.m_board[y_coord][x_coord] = std::make_unique<Rook>(x_coord, y_coord, board.getColor(currentPromotion));
                    flag = 1;
                    break;
    
                    


             }
        }
    }

    if (!flag) {
        return;
    }
    state = 0;
    changeStep(); 


}

void Game::move(Point pos) {
    auto [x_coord, y_coord] = pos.getCoords();
    if (x_coord >= 0 && x_coord < x_size && y_coord >= 0 && y_coord < y_size) {

        if (state == 1) {
            auto [x, y] = current.getCoords(); 
            if (board.m_board[y][x]->isValidMove({x_coord, y_coord}, board)) {
                if (board.m_board[y][x]->getType() == Piece::Type::King || (board.m_board[y][x]->getType() == Piece::Type::Rook && x == 7)) {
                    if (board.getColor(current) == Piece::Color::White) {
                        board.setWhiteCastle(false);
                    }
                    else {
                        board.setBlackCastle(false);
                    }
                } 
                
                board.m_board[y][x]->move(board, {x_coord, y_coord});
                ++step_count;

                if (board.m_board[y_coord][x_coord]->getType() == Piece::Type::Pawn && (y_coord == 0 || y_coord == 7)) {
                    std::cout << "stateee" << std::endl;
                    state = 2;
                    currentPromotion = Point(x_coord, y_coord);
                    return;

                }
                
                state = 0;
                checkCheckMates();
                checkStaleMates();
                changeStep();
                return;
            }
            else {
                if (board.isInCheck(Player(step))) {
                    setCurrent(Point(x_coord, y_coord));
                    std::cout << "You are in check" << std::endl;
                    return;
                }
            }
        }

        if (board.m_board[y_coord][x_coord] != nullptr) {

            setCurrent(Point(x_coord, y_coord));

            auto mov = board.m_board[y_coord][x_coord]->getMoveVector();
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

void Game::changeStep() {
    if (step == Piece::Color::White) {
        step = Piece::Color::Black;
    }
    else {
        step = Piece::Color::White;
    }


}

void Game::setCurrent(Point coord) {
    auto [x_coord, y_coord] = coord.getCoords();

    if (!board.isNull(coord)) {
        if (step == board.m_board[y_coord][x_coord]->getColor() && board.m_board[y_coord][x_coord]->getMoveVector().size() > 0) {
            state = 1;
            current = Point(x_coord, y_coord);
        }
        else {
            state = 0;
        }
    }

}


void Game::checkCheckMates() {
    if (board.isInCheckmate(whitePlayer)) {
        Draw();
        onCheckMate(whitePlayer);
    }
    else if (board.isInCheckmate(blackPlayer)) {
        Draw();
        onCheckMate(blackPlayer);
    }

}

void Game::checkStaleMates() {
    if (board.isInStalemate(whitePlayer)) {
        Draw();
        onStaleMate(whitePlayer);
    }
    else if (board.isInStalemate(blackPlayer)) {
        Draw();
        onStaleMate(blackPlayer);
    }

}

void Game::DrawPromotion(Point coord, Piece::Color color) {
    static std::string black_paths[] = {"../Piece_textures/b_bishop_1x.png", "../Piece_textures/b_knight_1x.png", "../Piece_textures/b_queen_1x.png", "../Piece_textures/b_rook_1x.png"};
    static std::string white_paths[] = {"../Piece_textures/w_bishop_1x.png", "../Piece_textures/w_knight_1x.png", "../Piece_textures/w_queen_1x.png", "../Piece_textures/w_rook_1x.png"};

    sf::Texture textures[4];

    auto [x, y] = coord.getCoords();
    if (color == Piece::Color::White) {
        for (int i = 0; i < 4; ++i) {
            if (!textures[i].loadFromFile(white_paths[i]))
                perror("Texture error");

            sprites[i].setTexture(textures[i]);
            
            sprites[i].setScale(0.12, 0.12);

            if (i < 2) {
                sprites[i].setPosition((x_size / BoardSize) * x + i * 50, (x_size / BoardSize) * y + i);
            }
            else {
                sprites[i].setPosition((x_size / BoardSize) * x + (i - 2) * 50, (x_size / BoardSize) * y + 50);
            }

            m_window.draw(sprites[i]);

        } 
    }
    else {
        for (int i = 0; i < 4; ++i) {
            if (!textures[i].loadFromFile(black_paths[i]))
                perror("Texture error");

            sprites[i].setTexture(textures[i]);

            sprites[i].setScale(0.12, 0.12);

            if (i < 2) {
                sprites[i].setPosition((x_size / BoardSize) * x + i * 50, (x_size / BoardSize) * y + i);
            }
            else {
                sprites[i].setPosition((x_size / BoardSize) * x + (i - 2) * 50, (x_size / BoardSize) * y + 50);
            }

            m_window.draw(sprites[i]);

        }
    }
}

void Game::onCheckMate(Player player) {
    std::cout << "Yeddd" << std::endl;
    if (player.getColor() == Piece::Color::Black) {
        std::cout << "White Wins!" << std::endl;
    }
    else {
        std::cout << "Black Wins" << std::endl;
    }
    exit(0);
}

void Game::onStaleMate(Player player) {
    std::cout << "Stalemate" << std::endl;
    exit(0);
}













