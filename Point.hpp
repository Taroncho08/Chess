#pragma once

#include <utility>

#include "Constants.hpp"


class Point
{
public:
    Point(int x, int y) : m_coordX(x), m_coordY(y) {}

    std::pair<int, int> getCoords() const;
    Point operator+(const Point& mv) const;
    Point operator-(const Point& mv) const;
    Point& operator+=(const Point& other);
    Point& operator-=(const Point& other);
    bool operator==(const Point& point);
    bool isValid();

private:
    int m_coordX;
    int m_coordY;
};
