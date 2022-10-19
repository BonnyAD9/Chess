#pragma once

#include <string>

namespace chess
{
    class Position
    {
    public:
        Position(int x, int y);
        Position(std::string pos);
        int GetX();
        int GetY();
        char GetXChr();
        char GetYChr();
        Position Abs();
        Position operator-(const Position &r);
        Position operator-();
        Position operator+(const Position &r);
        Position operator+();
        Position &operator+=(const Position &a);
        Position &operator-=(const Position &a);
        bool operator==(const Position &a) const;
        bool operator!=(const Position &a) const;
        Position operator*(const int &a);
        Position operator/(const int &a);
    private:
        int _x;
        int _y;
    };
} // namespace chess
