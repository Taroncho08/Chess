#include "Board.hpp"
#include "Pieces/Piece.hpp"
//#include "Constants.hpp"
#include <iostream>


void Board::update_moves() {
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (m_board[i][j] != nullptr) {
                m_board[i][j]->getMoves(*this);
            }
        }
    }

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

void Board::setWhiteCastle(bool val) {
    whiteCastle = val;
}

bool Board::canWhiteCastle() const {
    return whiteCastle;
}

bool Board::canBlackCastle() const {
    return blackCastle;
}

void Board::setBlackCastle(bool val) {
    blackCastle = val;
}

void Board::setupEmpty() {
    for (int i = 2; i < BoardSize - 2; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            m_board[i][j] = nullptr;
        }
    }
}

bool Board::isLeftSideEmpty(Piece::Color color) const {
    if (color == Piece::Color::Black) {
        for (int i = 1; i < 4; ++i) {
            if (m_board[0][i] != nullptr) {
                return false;
            }
        }
    }
    else {
        for (int i = 1; i < 4; ++i) {
            if (m_board[7][i] != nullptr) {
                return false;
            }
        }
    }
    return true;
}

bool Board::isRightSideEmpty(Piece::Color color) const {
    if (color == Piece::Color::Black) {
        for (int i = 5; i < 7; ++i) {
            if (m_board[0][i] != nullptr) {
                return false;
            }
        }
    }
    else {
        for (int i = 5; i < 7; ++i) {
            if (m_board[7][i] != nullptr) {
                return false;
            }
        }
    }
    return true;
   
}

bool Board::canCastleToRight(Piece::Color color) {
    if (color == Piece::Color::Black) {
        if ((m_board[0][4] != nullptr && m_board[0][4]->getType() == Piece::Type::King && !m_board[0][4]->gethasMoved())
                && (m_board[0][7] != nullptr && m_board[0][7]->getType() == Piece::Type::Rook && !m_board[0][7]->gethasMoved())
                && isRightSideEmpty(color)) {
            return true;
        }
    }
    else {
        if ((m_board[7][4] != nullptr && m_board[7][4]->getType() == Piece::Type::King && !m_board[7][4]->gethasMoved())
                && (m_board[7][7] != nullptr && m_board[7][7]->getType() == Piece::Type::Rook && !m_board[7][7]->gethasMoved())
                && isRightSideEmpty(color)) {
            return true;
        }
    }
    return false;
}


bool Board::canCastleToLeft(Piece::Color color) {
    if (color == Piece::Color::Black) {
        if ((m_board[0][4] != nullptr && m_board[0][4]->getType() == Piece::Type::King && !m_board[0][4]->gethasMoved())
                && (m_board[0][0] != nullptr && m_board[0][0]->getType() == Piece::Type::Rook && !m_board[0][0]->gethasMoved())
                && isLeftSideEmpty(color)) {
            return true;
        }
    }
    else {
        if ((m_board[7][4] != nullptr && m_board[7][4]->getType() == Piece::Type::King && !m_board[7][4]->gethasMoved())
                && (m_board[7][0] != nullptr && m_board[7][0]->getType() == Piece::Type::Rook && !m_board[7][0]->gethasMoved())
                && isLeftSideEmpty(color)) {
            return true;
        }
    }
    return false;

}


void Board::printPieces(sf::RenderWindow &window, int window_size, int state, Point promotionCoords) {
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (m_board[i][j] != nullptr) {
                if (state == 2 && Point (j, i) == promotionCoords) {
                    continue;
                }
                m_board[i][j]->draw(window, window_size);
            }
        }
    }
}

bool Board::isNull(Point pos) {
    auto[x, y] = pos.getCoords();
    if(m_board[y][x] == nullptr) {
        return true;
    }
    return false;
}

void Board::addMoveToPiece(Point coord, Point move) {
    auto [x, y] = coord.getCoords();
    m_board[y][x]->addMove(move);
}

void Board::setNull(Point pos) {
    auto [x, y] = pos.getCoords();
    std::cout << "Null object_x: " << x << " And y: " << y << std::endl;
    m_board[y][x] = nullptr;
}

std::array<std::array<std::unique_ptr<Piece>, BoardSize>, BoardSize> Board::copy() const {

    std::array<std::array<std::unique_ptr<Piece>, BoardSize>, BoardSize> result;

    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (m_board[i][j]) {
                result[i][j] = m_board[i][j]->clone();

            }
        }
    }
    return result;
}



Piece::Color Board::getColor(Point pos) const {
    auto [x, y] = pos.getCoords();
    return m_board[y][x]->getColor();
}
 
Piece::Type Board::getType(Point pos) {
    auto [x, y] = pos.getCoords();
    return m_board[y][x]->getType();
}

bool Board::isInCheck(Player player) {
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (m_board[i][j] != nullptr) {
                if (m_board[i][j]->canCaptureOpponentKing(*this, player)) {
                    return true;
                }
            }
        }
    }    
    return false;
    
}

bool Board::hasValidMoves(Player player) {
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (m_board[i][j] != nullptr) {
         
                for (auto move : m_board[i][j]->getMoveVector()) {
                    if (m_board[i][j]->isValidMove(move, *this) && getColor(Point{j, i}) == player.getColor()) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Board::isInCheckmate(Player player) {
    if (isInCheck(player) && !hasValidMoves(player)) {
        return true;
    }

    return false;

}

bool Board::isInStalemate(Player player) {
    if (!isInCheck(player) && !hasValidMoves(player)) {
        return true;
    }
return false;
}

void Board::setCoords(Point point, Point coords) {
    auto [x, y] = point.getCoords();
    m_board[y][x]->setPosition(coords);
}

void Board::setPosition(Point from, Point to) {
    auto [from_x, from_y] = from.getCoords();
    auto [to_x, to_y] = to.getCoords();

    m_board[to_y][to_x] = std::move(m_board[from_y][from_x]);
    m_board[from_y][from_x] = nullptr;
    
}

void Board::print() {
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (m_board[i][j]) {
                std::cout << int(m_board[i][j]->getType());
            }
            else {
                std::cout << " ";
            }
        }

        std::cout << "\n";
    
    }
}

