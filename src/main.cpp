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

    std::cin.get();
    std::cin.get();

    std::cout << "\x1b[?1049l";
}

void DrawBoard(chess::Board &b)
{
    std::cout << "  ";
    for (int x = 0; x < 8; ++x)
        std::cout << chess::Position(x, 0).GetXChr() << ' ';

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
                DrawPiece(b.GetUnrot(x, y));
            }
            else
            {
                std::cout << "\x1b[7m";
                DrawPiece(chess::Other(b.GetUnrot(x, y)));
            }
            if (x != 7)
                std::cout << "▐";
            if (x == 7)
                std::cout << (y & 1 ? "▐\x1b[0m" : "\x1b[0m ");
        }

        std::cout << chess::Position(0, y).GetYChr() << (y & 1 ? " " : "▐");
        for (int x = 0; x < 8; ++x)
        {
            if (x + y & 1)
            {
                std::cout << "\x1b[0m";
                DrawPiece(b.GetUnrot(7 - x, 7 - y));
            }
            else
            {
                std::cout << "\x1b[7m";
                DrawPiece(chess::Other(b.GetUnrot(7 - x, 7 - y)));
            }
            if (x != 7)
                std::cout << "▐";
            if (x == 7)
                std::cout << (y & 1 ? "▐\x1b[0m" : "\x1b[0m ");
        }
        std::cout << chess::Position(0, y).GetYChr();
        std::cout << "\x1b[0m" << std::endl;
    }

    std::cout << "  ";
    for (int x = 0; x < 8; ++x)
        std::cout << chess::Position(x, 0).GetXChr() << ' ';

    std::cout << "  ";
    for (int x = 0; x < 8; ++x)
        std::cout << chess::Position(x, 0).GetXChr() << ' ';
    std::cout << std::endl;
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
