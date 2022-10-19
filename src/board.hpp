#pragma once

#include <array>

#include "piece.hpp"
#include "position.hpp"

namespace chess
{
    class Board
    {
    public:
        Board();
        Piece GetOnTurn();
        bool Move(Position from, Position to);
        Piece Get(Position pos);
    private:
        Piece _onTurn;
        bool _CheckCheck(Piece def);
        bool _CheckCheckmate(Piece def);
        void _BackupBoard();
        void _ReloadBoard();
        bool _CanMove(Position from, Position to);
        bool _CanPawnMove(Position from, Position to);
        bool _CanBishopMove(Position from, Position to);
        bool _CanKnightMove(Position from, Position to);
        bool _CanRookMove(Position from, Position to);
        bool _CanQueenMove(Position from, Position to);
        bool _CanKingMove(Position from, Position to);
        Piece &_At(Position pos);
        Piece &_At(int x, int y);
        std::array<std::array<Piece, 8>, 8> _board;
        std::array<std::array<Piece, 8>, 8> _cboard;
    };
} // namespace chess
