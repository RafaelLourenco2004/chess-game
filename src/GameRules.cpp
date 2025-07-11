#include <iostream>
#include "GameRules.h"
#include "Pawn.h"
#include "Board.h"

bool GameRules::can_move(Piece &piece, const Board &board, const string &from, const string &to)
{
    auto can_piece_move = [&board](const string &origin, const string &dest)
    {
        if (!board.is_valid_square(dest) || !board.is_valid_square(origin))
        {
            std::cout << "INVALID SQUARE" << std::endl;
            return false;
        }

        if (board.is_square_occoupied(origin))
        {
            if (origin == dest)
                return true;
            std::cout << "OCCUPIED" << std::endl;
            return false;
        }

        return true;
    };

    return piece.can_move(from, to, can_piece_move);
}

bool GameRules::can_capture(Piece *piece, const Board &board, const std::string &from, const std::string &to)
{
    Pawn *pawn = dynamic_cast<Pawn *>(piece);
    if (pawn != nullptr)
        return pawn->can_capture(from, to);

    return can_move(*piece, board, from, to);
}
