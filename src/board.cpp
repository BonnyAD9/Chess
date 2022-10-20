#include "board.hpp"

namespace chess
{
    Board::Board() : _onTurn(Piece::white), _win(0), _board()
    {
        _board[0][0] = Piece::white_rook;
        _board[1][0] = Piece::white_knight;
        _board[2][0] = Piece::white_bishop;
        _board[3][0] = Piece::white_king;
        _board[4][0] = Piece::white_queen;
        _board[5][0] = Piece::white_bishop;
        _board[6][0] = Piece::white_knight;
        _board[7][0] = Piece::white_rook;

        for (int x = 0; x < 8; ++x)
            _board[x][1] = Piece::white_pawn;

        for (int x = 0; x < 8; ++x)
        {
            for (int y = 2; y < 6; ++y)
                _board[x][y] = Piece::none;
        }

        for (int x = 0; x < 8; ++x)
            _board[x][6] = Piece::black_pawn;

        _board[0][7] = Piece::black_rook;
        _board[1][7] = Piece::black_knight;
        _board[2][7] = Piece::black_bishop;
        _board[3][7] = Piece::black_king;
        _board[4][7] = Piece::black_queen;
        _board[5][7] = Piece::black_bishop;
        _board[6][7] = Piece::black_knight;
        _board[7][7] = Piece::black_rook;
    }

    bool Board::Move(Position from, Position to)
    {
        _BackupBoard();
        if (to.GetX() > 7 || to.GetX() < 0 ||
            to.GetY() > 7 || to.GetY() < 0 ||
            from.GetX() > 7 || from.GetY() < 0 ||
            from.GetY() > 7 || from.GetY() < 0)
            return false;

        if (_At(from) == Piece::none ||
            IsWhite(_At(from)) ^ IsWhite(_onTurn) ||
            !_CanMove(from, to))
            return false;

        _At(to) = _At(from);
        _At(from) = Piece::none;
        if (_CheckCheck(_onTurn))
        {
            _ReloadBoard();
            return false;
        }
        _onTurn = Other(_onTurn);
        _win = _CheckEnd(_onTurn);
        return true;
    }

    Piece Board::GetOnTurn() { return _onTurn; }

    Piece Board::Get(Position pos)
    {
        return _At(pos);
    }

    int Board::GetWin() { return _win; }

    bool Board::_CheckCheck(Piece def)
    {
        auto pos = _FindPiece(static_cast<Piece>(
            static_cast<int>(Piece::king) |
            static_cast<int>(def)
        ));

        if (pos == Position(-1, -1))
            return false;

        for (int y = 0; y < 8; ++y)
        {
            for (int x = 0; x < 8; ++x)
            {
                if (_CanMove(Position(x, y), pos))
                    return true;
            }
        }
        return false;
    }

    int Board::_CheckEnd(Piece def)
    {
        auto pos = _FindPiece(static_cast<Piece>(
            static_cast<int>(Piece::king) |
            static_cast<int>(def)
        ));

        if (pos == Position(-1, -1))
            return 0;

        if (!_CheckCheck(def))
            return _CanKingUncheck(def) ? 0 : -1;
        _BackupBoard();
        auto ret = _CanKingUncheck(def);
        _ReloadBoard();
        if (ret)
            return 0;
        return 1;
    }

    Position Board::_FindPiece(Piece p)
    {
        for (int y = 0; y < 8; ++y)
        {
            for (int x = 0; x < 8; ++x)
            {
                if (_At(x, y) == p)
                    return Position(x, y);
            }
        }
        return Position(-1, -1);
    }

    bool Board::_CanKingUncheck(Piece def)
    {
        for (int y = 0; y < 8; ++y)
        {
            for (int x = 0; x < 8; ++x)
            {
                _ReloadBoard();
                if (IsWhite(def) == IsWhite(_At(x, y)) &&
                    _CanMoveUncheck(Position(x, y)))
                    return true;
            }
        }
        return false;
    }

    bool Board::_CanMoveUncheck(Position from)
    {
        for (int y = 0; y < 8; ++y)
        {
            for (int x = 0; x < 8; ++x)
            {
                if (_CanMove(from, Position(x, y)) &&
                    !_CheckCheck(static_cast<Piece>(IsWhite(_At(from)))))
                    return true;
            }
        }
        return false;
    }

    void Board::_BackupBoard()
    {
        for (int i = 0; i < 8; ++i)
            std::copy(_board[i].begin(), _board[i].end(), _cboard[i].begin());
    }

    void Board::_ReloadBoard()
    {
        for (int i = 0; i < 8; ++i)
            std::copy(_cboard[i].begin(), _cboard[i].end(), _board[i].begin());
    }

    bool Board::_CanMove(Position from, Position to)
    {
        if (_At(to) != Piece::none && IsWhite(_At(from)) == IsWhite(_At(to)))
            return false;

        switch (GetType(_At(from)))
        {
        case Piece::pawn:
            return _CanPawnMove(from, to);
        case Piece::bishop:
            return _CanBishopMove(from, to);
        case Piece::knight:
            return _CanKnightMove(from, to);
        case Piece::rook:
            return _CanRookMove(from, to);
        case Piece::queen:
            return _CanQueenMove(from, to);
        case Piece::king:
            return _CanKingMove(from, to);
        default:
            return false;
        }
    }

    bool Board::_CanPawnMove(Position from, Position to)
    {
        auto p = Position(0, -1);

        if (to - from == p)
            return true;

        if (to - from == p * 2)
        {
            if (from.GetY() != 6)
                return false;
            return _At(from - p) != Piece::none;
        }

        if (_At(to) == Piece::none)
            return false;

        return to - from == p + Position(1, 0) ||
            to - from == p + Position(-1, 0);
    }

    bool Board::_CanBishopMove(Position from, Position to)
    {
        auto dif = to - from;
        if (abs(dif.GetX()) != abs(dif.GetY()))
            return false;

        dif = dif / abs(dif.GetX());

        for (from += dif; from != to; from += dif)
        {
            if (_At(from) != Piece::none)
                return false;
        }

        return true;
    }

    bool Board::_CanKnightMove(Position from, Position to)
    {
        auto path = (from - to).Abs();
        return path == Position(2, 1) || path == Position(1, 2);
    }

    bool Board::_CanRookMove(Position from, Position to)
    {
        auto dif = to - from;
        if (dif.GetX() != 0 && dif.GetY() != 0)
            return false;

        dif = dif / abs(dif.GetX() + dif.GetY());

        for (from += dif; from != to; from += dif)
        {
            if (_At(from) != Piece::none)
                return false;
        }
        return false;
    }

    bool Board::_CanQueenMove(Position from, Position to)
    {
        return _CanBishopMove(from, to) || _CanRookMove(from, to);
    }

    bool Board::_CanKingMove(Position from, Position to)
    {
        auto div = (from - to).Abs();
        return div.GetX() < 2 && div.GetY() < 2;
    }

    Piece &Board::_At(Position pos)
    {
        return _At(pos.GetX(), pos.GetY());
    }

    Piece &Board::_At(int x, int y)
    {
        return IsWhite(_onTurn)
            ? _board[7 - x][7 - y]
            : _board[x][y];
    }
} // namespace chess
