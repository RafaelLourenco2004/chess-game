#include <string>
#include <cmath>
#include "Knight.h"

using std::abs;

Knight::Knight(char type, enum Color colour) : Piece(type, colour)
{
}

bool Knight::can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move) const
{
    int origin_col = static_cast<int>(from.at(0));
    int origin_row = from.at(1) - '0';
    int dest_col = static_cast<int>(to.at(0));
    int dest_row = to.at(1) - '0';

    if ((abs(dest_row - origin_row) == 2 && abs(dest_col - origin_col) == 1) ||
        (abs(dest_row - origin_row) == 1 && abs(dest_col - origin_col) == 2))
    {
        return can_piece_move(to, to);
    }
    return false;
}