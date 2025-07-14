#include <string>

#include "GameRules.h"
#include "Pawn.h"
#include "Board.h"
#include "King.h"
#include "Rook.h"

// bool GameRules::is_in_check(Piece &piece, const string &to, const string &from, Color turn)
// {
//     return true;
// }

bool GameRules::can_move(Piece &piece, const string &from, const string &to)
{
    auto can_piece_move = [&](const string &origin, const string &dest)
    {
        if (!board.is_valid_square(dest) || !board.is_valid_square(origin))
        {
            return false;
        }

        if (board.is_square_occoupied(origin))
        {
            if (origin == dest)
                return true;
            return false;
        }

        return true;
    };

    return piece.can_move(from, to, can_piece_move);
}

bool GameRules::can_capture(Piece *piece, const std::string &from, const std::string &to)
{
    Pawn *pawn = dynamic_cast<Pawn *>(piece);
    if (pawn != nullptr)
        return pawn->can_capture(from, to);

    return can_move(*piece, from, to);
}

bool GameRules::can_castle(Piece *piece_a, Piece *piece_b, const string &from, const string &to)
{
    King *king = nullptr;
    Rook *rook = nullptr;
    string king_pos;
    string rook_pos;
    if (board.is_type<King>(piece_a))
    {
        king = dynamic_cast<King *>(piece_a);
        rook = dynamic_cast<Rook *>(piece_b);
        king_pos = from;
        rook_pos = to;
    }
    else
    {
        king = dynamic_cast<King *>(piece_b);
        rook = dynamic_cast<Rook *>(piece_a);
        king_pos = to;
        rook_pos = from;
    }

    if (king->has_king_moved() || rook->has_rook_moved())
    {
        return false;
    }

    int king_col = king_pos.at(0) - 'A';
    int rook_col = rook_pos.at(0) - 'A';
    char row = king_pos.at(1);

    int offset = rook_col > king_col ? 1 : -1;
    string square;
    for (int col = king_col + offset; col != rook_col; col += offset)
    {
        square = string(1, static_cast<char>(col + 'A')) + string(1, row);
        std::cout << square << std::endl;
        if (board.is_square_occoupied(square))
        {
            return false;
        }
    }
    return true;
}
