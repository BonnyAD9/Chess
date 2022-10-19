#include "piece.hpp"

namespace chess
{
    bool IsWhite(Piece p)
    {
        return static_cast<int>(p) & static_cast<int>(Piece::white);
    }

    Piece GetType(Piece p)
    {
        return static_cast<Piece>(
            static_cast<int>(p) & static_cast<int>(Piece::type)
        );
    }

    Piece Other(Piece p)
    {
        return static_cast<Piece>(
            static_cast<int>(p) ^ static_cast<int>(Piece::white)
        );
    }
} // namespace chess
