#include "Player.hpp"

Player::Player(Piece::Color color) : m_points(0), m_color(color) {}

void Player::setPoints(int val) {
    m_points = val;
}

int Player::getPoints() {
    return m_points;
}

Piece::Color Player::getColor() {
    return m_color;
}
