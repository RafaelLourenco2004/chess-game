#include <cmath>
#include <string>
#include "Queen.h"

Queen::Queen(char type, enum Color colour) : Piece(type, colour)
{
}

bool Queen::can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move,
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

bool Queen::can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move,
                     bool horizontal, int offset) const
{
    int origin_col = static_cast<int>(from.at(0));
    int origin_row = from.at(1) - '0';

    string pos_col = horizontal ? string(1, static_cast<char>(origin_col + offset)) : string(1, static_cast<char>(origin_col));
    string pos_row = horizontal ? std::to_string(origin_row) : std::to_string(origin_row + offset);
    string pos = pos_col + pos_row;

    while (can_piece_move(pos, to))
    {
        if (pos == to)
            return true;

        if (horizontal)
        {
            origin_col += offset;
            pos = string(1, static_cast<char>(origin_col)) + pos_row;
        }
        else
        {
            origin_row += offset;
            pos = pos_col + std::to_string(origin_row);
        }
    }
    return false;
}

bool Queen::can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move) const
{
    int origin_col = static_cast<int>(from.at(0));
    int origin_row = from.at(1) - '0';
    int dest_col = static_cast<int>(to.at(0));
    int dest_row = to.at(1) - '0';

    if (dest_row != origin_row && dest_col != origin_col)
    {
        if (std::abs(dest_row - origin_row) != std::abs(dest_col - origin_col))
            return false;

        int row_offset = dest_row > origin_row ? 1 : -1;
        int col_offset = dest_col > origin_col ? 1 : -1;
        std::pair<int, int> offset = std::make_pair(row_offset, col_offset);
        return can_move(from, to, can_piece_move, offset);
    }

    int offset;
    if (origin_row == dest_row)
    {
        offset = dest_col > origin_col ? 1 : -1;
        return can_move(from, to, can_piece_move, true, offset);
    }

    offset = dest_row > origin_row ? 1 : -1;
    return can_move(from, to, can_piece_move, false, offset);
}