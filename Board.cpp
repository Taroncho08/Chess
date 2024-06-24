#include "Board.hpp"

Board::Board() {
    setupBoard();
}

void Board::setupBoard() {
    for (int i = 0; i < BoardSize; ++i) {
        m_board[1][i] = std::make_unique<Pawn>(i, 1, Piece::Color::Black);
        m_board[6][i] = std::make_unique<Pawn>(i, 6, Piece::Color::White);
    }

    setupPiecesRow(0, Piece::Color::Black, {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'});
    setupPiecesRow(7, Piece::Color::White, {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'});
    setupEmpty();
}

void Board::setupPiecesRow(int row, Piece::Color color, const std::vector<char>& pieceTypes) {
    for (int col = 0; col < BoardSize; ++col) {
        switch (pieceTypes[col]) {
        case 'R':
            m_board[row][col] = std::make_unique<Rook>(col, row, color);
            break;
        case 'N':
            m_board[row][col] = std::make_unique<Knight>(col, row, color);
            break;
        case 'B':
            m_board[row][col] = std::make_unique<Bishop>(col, row, color);
            break;
        case 'Q':
            m_board[row][col] = std::make_unique<Queen>(col, row, color);
            break;
        case 'K':
            m_board[row][col] = std::make_unique<King>(col, row, color);
            break;
        default:
            break;
        }
    }
}

void Board::setupEmpty() {
    for (int i = 2; i < BoardSize - 2; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            m_board[i][j] = {nullptr};
        }
    }
}

void Board::printPieces(sf::RenderWindow &window, int window_size) {
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (m_board[i][j] != nullptr) {
                m_board[i][j]->draw(window, window_size);
            }
        }
    }
}

bool Board::isNull(int y, int x) {
    if(m_board[y][x] == nullptr) {
        return true;
    }
    return false;
}

Piece::Color Board::getColor(int x, int y) {
    return m_board[y][x]->getColor();
}


