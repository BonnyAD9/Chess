#pragma once

namespace chess
{
    enum class Piece
    {
        none  = 0,
        black = 0,
        white = 1,
        type  = 0xE,

        pawn   = 2,
        bishop = 4,
        knight = 6,
        rook   = 8,
        queen  = 10,
        king   = 12,

        black_pawn   = 2,
        black_bishop = 4,
        black_knight = 6,
        black_rook   = 8,
        black_queen  = 10,
        black_king   = 12,

        white_pawn   = 3,
        white_bishop = 5,
        white_knight = 7,
        white_rook   = 9,
        white_queen  = 11,
        white_king   = 13,
    };

    bool IsWhite(Piece p);
    Piece GetType(Piece p);
    Piece Other(Piece p);
} // namespace chess
