#include "King.h"

King::King(char type, enum Color colour) : Piece(type, colour), StatefulPiece()
{
}

bool King::can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move) const
{
    int origin_col = static_cast<int>(from.at(0));
    int origin_row = from.at(1) - '0';
    int dest_col = static_cast<int>(to.at(0));
    int dest_row = to.at(1) - '0';

    if (std::abs(dest_row - origin_row) > 1 || std::abs(dest_col - origin_col) > 1)
        return false;

    if (can_piece_move(to, to))
    {
        return true;
    }
    return false;
}