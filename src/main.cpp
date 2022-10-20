#include <iostream>
#include "board.hpp"

void DrawBoard(chess::Board &b);
void DrawPiece(chess::Piece p);
// u_c=i/C
int main()
{
    std::cout << "\x1b[?1049h";
    chess::Board b;
    while (!b.GetWin())
    {
        std::cout << "\x1b[2J\x1b[H";
        DrawBoard(b);
        std::cout << (
            chess::IsWhite(b.GetOnTurn())
                ? "white > "
                : "black > "
        );
        std::string from;
        std::string to;

        std::cin >> from;
        if (from == "quit")
            break;

        std::cin >> to;

        if (std::cin.bad())
        {
            std::cin.clear();
            continue;
        }

        b.Move(chess::Position(from), chess::Position(to));
    }

    std::cout << "\x1b[?1049l";

    switch (b.GetWin())
    {
    case -1:
        std::cout << "Tie!" << std::endl;
        break;
    case 1:
        std::cout << (
            chess::IsWhite(b.GetOnTurn())
                ? "black won"
                : "white won"
        ) << std::endl;
        break;
    }

}

void DrawBoard(chess::Board &b)
{
    std::cout << "  ";
    for (int x = 0; x < 8; ++x)
        std::cout << chess::Position(x, 0).GetXChr() << ' ';
    std::cout << std::endl;

    for (int y = 0; y < 8; ++y)
    {
        std::cout << chess::Position(0, y).GetYChr() << (y & 1 ? " " : "▐");
        for (int x = 0; x < 8; ++x)
        {
            if (x + y & 1)
            {
                std::cout << "\x1b[0m";
                DrawPiece(b.Get(chess::Position(x, y)));
            }
            else
            {
                std::cout << "\x1b[7m";
                DrawPiece(chess::Other(b.Get(chess::Position(x, y))));
            }
            if (x != 7 || y & 1)
                std::cout << "▐";
        }
        std::cout << "\x1b[0m" << std::endl;
    }
}

void DrawPiece(chess::Piece p)
{
    switch (p)
    {
    case chess::Piece::none:
    case chess::Piece::white:
        std::cout << " ";
        break;
    case chess::Piece::black_pawn:
        std::cout << "♙";
        break;
    case chess::Piece::black_bishop:
        std::cout << "♗";
        break;
    case chess::Piece::black_knight:
        std::cout << "♘";
        break;
    case chess::Piece::black_rook:
        std::cout << "♖";
        break;
    case chess::Piece::black_queen:
        std::cout << "♕";
        break;
    case chess::Piece::black_king:
        std::cout << "♔";
        break;
    case chess::Piece::white_pawn:
        std::cout << "♟";
        break;
    case chess::Piece::white_bishop:
        std::cout << "♝";
        break;
    case chess::Piece::white_knight:
        std::cout << "♞";
        break;
    case chess::Piece::white_rook:
        std::cout << "♜";
        break;
    case chess::Piece::white_queen:
        std::cout << "♛";
        break;
    case chess::Piece::white_king:
        std::cout << "♚";
        break;
    default:
        std::cout << "?";
        break;
    }
}
