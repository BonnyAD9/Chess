#include "position.hpp"

namespace chess
{
    int _FromChar(int chr);

    Position::Position(int x, int y) : _x(x), _y(y) { }

    Position::Position(std::string pos) :
        _x(_FromChar(pos[0])),
        _y(_FromChar(pos[1]))
    { }

    int Position::GetX() { return _x; }
    int Position::GetY() { return _y; }

    char Position::GetXChr() { return _x + 'a'; }
    char Position::GetYChr() { return '8' - _y; }

    int _FromChar(int chr)
    {
        chr = tolower(chr);
        if (chr >= 'a' && chr <= 'h')
            return chr - 'a';

        if (chr >= '1' && chr <= '8')
            return '8' - chr;

        return 0;
    }

    Position Position::Abs()
    {
        return Position(abs(_x), abs(_y));
    }

    Position Position::operator-()
    {
        return Position(-_x, -_y);
    }

    Position Position::operator-(const Position &r)
    {
        return Position(_x - r._x, _y - r._y);
    }

    Position Position::operator+()
    {
        return Position(_x, _y);
    }

    Position Position::operator+(const Position &r)
    {
        return Position(_x + r._x, _y + r._y);
    }

    Position &Position::operator+=(const Position &a)
    {
        _x += a._x;
        _y += a._y;
        return *this;
    }

    Position &Position::operator-=(const Position &a)
    {
        _x -= a._x;
        _y -= a._y;
        return *this;
    }

    bool Position::operator==(const Position &a) const
    {
        return _x == a._x && _y == a._y;
    }

    bool Position::operator!=(const Position &a) const
    {
        return !(*this == a);
    }

    Position Position::operator*(const int &a)
    {
        return Position(_x * a, _y * a);
    }

    Position Position::operator/(const int &a)
    {
        return Position(_x / a, _y / a);
    }
} // namespace chess
