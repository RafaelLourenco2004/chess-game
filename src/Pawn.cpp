#include <string>
#include <cmath>
#include "Pawn.h"

using std::abs;

Pawn::Pawn(char type, enum Color colour) : Piece(type, colour), StatefulPiece()
{
}

bool Pawn::can_push(int offset) const
{
    if (colour == WHITE && offset < 0)
        return false;

    if (colour == BLACK && offset > 0)
        return false;

    return true;
}

bool Pawn::can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move) const
{
    int origin_col = static_cast<int>(from.at(0));
    int origin_row = from.at(1) - '0';
    int dest_col = static_cast<int>(to.at(0));
    int dest_row = to.at(1) - '0';

    if (dest_col != origin_col)
        return false;

    int offset = dest_row - origin_row;

    if (abs(offset) == 2)
    {
        if (has_moved())
            return false;

        if (!can_push(offset))
            return false;

        return true;
    }

    if (abs(offset) == 1)
    {
        if (!can_push(offset))
            return false;

        return true;
    }

    return false;
}

bool Pawn::can_capture(const string &from, const string &to)
{
    int origin_col = static_cast<int>(from.at(0));
    int origin_row = from.at(1) - '0';
    int dest_col = static_cast<int>(to.at(0));
    int dest_row = to.at(1) - '0';

    if (abs(dest_row - origin_row) != 1 || abs(dest_col - origin_col) != 1)
        return false;

    int offset = dest_row - origin_row;
    if (!can_push(offset))
        return false;

    return true;
}