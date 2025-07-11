#include <string>
#include <cmath>
#include "Bishop.h"

Bishop::Bishop(char type, enum Color colour) : Piece(type, colour)
{
}

bool Bishop::can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move,
                      std::pair<int, int> offset) const
{
    int origin_col = static_cast<int>(from.at(0));
    int origin_row = from.at(1) - '0';

    origin_row += offset.first;
    origin_col += offset.second;
    string pos = string(1, static_cast<char>(origin_col)) + std::to_string(origin_row);
    while (can_piece_move(pos, to))
    {
        if (pos == to)
            return true;
        origin_row += offset.first;
        origin_col += offset.second;
        pos = string(1, static_cast<char>(origin_col)) + std::to_string(origin_row);
    }
    return false;
}

bool Bishop::can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move)
{
    char origin_col = from.at(0);
    char origin_row = from.at(1);
    char dest_col = to.at(0);
    char dest_row = to.at(1);

    if (origin_col == dest_col)
        return false;

    if (origin_row == dest_row)
        return false;

    if (std::abs(dest_row - origin_row) != std::abs(dest_col - origin_col))
        return false;

    int row_offset = dest_row > origin_row ? 1 : -1;
    int col_offset = dest_col > origin_col ? 1 : -1;
    std::pair<int, int> offset = std::make_pair(row_offset, col_offset);

    return can_move(from, to, can_piece_move, offset);
}