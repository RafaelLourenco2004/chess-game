#include "GameRules.h"
#include "Board.h"

bool GameRules::can_move(const Piece &piece, const Board &board, const string &from, const string &to)
{
    auto can_piece_move = [&board](const string &dest)
    {
        if (!board.is_valid_square(dest))
            return false;

        if (board.is_square_occoupied(dest))
            return false;

        return true;
    };

    return piece.can_move(from, to, can_piece_move);
}

// bool GameRules::can_capture(const Piece &piece, const Board &board, const std::string &from, const std::string &to)
// {
//     auto can_piece_capture = [&board](const string &dest)
//     {
//         if (!board.is_valid_square(dest))
//             return false;

//         if (board.is_square_occoupied(dest))
//             return false;

//         return true;
//     };


// }