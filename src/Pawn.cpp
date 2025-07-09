#include <string>

#include "Pawn.h"

Pawn::Pawn(char type, enum Color colour) : Piece(type, colour), has_moved{false}
{
}

bool Pawn::can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move) const
{
    char column = from.at(0);
    int row = from.at(1) - '0';

    string pos = string(1, column) + std::to_string(row + 1);
    if (can_piece_move(pos) && pos == to)
        return true;

    if (!has_moved)
    {
        pos = string(1, column) + std::to_string(row + 2);
        if (can_piece_move(pos) && pos == to)
            return true;
    }

    return false;
}

bool Pawn::can_capture(const string &from, const string &to, std::function<bool(string)> can_piece_move)
{
    return true;
}