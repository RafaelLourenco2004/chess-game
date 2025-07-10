#include <string>

#include "Pawn.h"

Pawn::Pawn(char type, enum Color colour) : Piece(type, colour), has_moved{false}
{
}

bool Pawn::can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move)
{
    char column = from.at(0);

    int origin_row = from.at(1) - '0';
    int dest_row = to.at(1) - '0';

    int offset = dest_row > origin_row ? 1 : -1;

    string pos = string(1, column) + std::to_string(origin_row + offset);
    if (can_piece_move(pos) && pos == to)
        return true;

    if (!has_moved)
    {
        pos = string(1, column) + std::to_string(origin_row + (2 * offset));
        if (can_piece_move(pos) && pos == to)
        {
            has_moved = true;
            return true;
        }
    }

    return false;
}

bool Pawn::can_capture(const string &from, const string &to, std::function<bool(string)> can_piece_move)
{
    
}