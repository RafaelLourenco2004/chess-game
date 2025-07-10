#include <string>
#include "Rook.h"

Rook::Rook(char type, enum Color colour) : Piece(type, colour), has_moved{false}
{
}

bool Rook::can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move,
                    bool horizontal, int offset)
{
    int origin_col = static_cast<int>(from.at(0));
    int origin_row = from.at(1) - '0';

    string pos_col = horizontal ? string(1, static_cast<char>(origin_col + offset)) : string(1, static_cast<char>(origin_col));
    string pos_row = horizontal ? std::to_string(origin_row) : std::to_string(origin_row + offset);
    string pos = pos_col + pos_row;

    while (can_piece_move(pos))
    {
        if (pos == to)
        {
            has_moved = true;
            return true;
        }

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

bool Rook::can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move)
{
    int origin_col = static_cast<int>(from.at(0));
    int origin_row = from.at(1) - '0';
    int dest_col = static_cast<int>(to.at(0));
    int dest_row = to.at(1) - '0';
    if (origin_col != dest_col && origin_row != dest_row)
        return false;

    int offset;
    if (origin_row == dest_row)
    {
        offset = dest_col > origin_col ? 1 : -1;
        return can_move(from, to, can_piece_move, true, offset);
    }

    offset = dest_row > origin_row ? 1 : -1;
    return can_move(from, to, can_piece_move, false, offset);
}