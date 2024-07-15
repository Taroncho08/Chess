#include "Point.hpp"

std::pair<int, int> Point::getCoords() const
{
    return std::make_pair(m_coordX, m_coordY);
}

Point Point::operator+(const Point& mv) const
{
    Point tmp(this->m_coordX + mv.m_coordX, this->m_coordY + mv.m_coordY);
    return tmp;
}

bool Point::isValid() {
    auto [x, y] = getCoords();
    return x >= 0 && x < BoardSize && y >= 0 && y < BoardSize;
}

Point& Point::operator+=(const Point& other) {
    m_coordX = m_coordX + other.m_coordX;
    m_coordY = m_coordY + other.m_coordY;
    return *this;
}

bool Point::operator==(const Point& point) const {
    auto[x, y] = point.getCoords();

    if (x == m_coordX && y == m_coordY) {
        return true;
    }

    return false;
}

Point Point::operator-(const Point& mv) const {
    Point tmp(this->m_coordX - mv.m_coordX, this->m_coordY - mv.m_coordY);
    return tmp;
}

Point& Point::operator-=(const Point& other) {
    m_coordX = m_coordX - other.m_coordX;
    m_coordY = m_coordY - other.m_coordY;
    return *this;
}
