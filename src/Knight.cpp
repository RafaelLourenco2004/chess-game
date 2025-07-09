#include <string>
#include "Knight.h"

Knight::Knight(char type, enum Color colour) : Piece(type, colour)
{
}

std::vector<string> Knight::get_possible_moves(const string &square, std::function<bool(string)> can_piece_move) const
{
    std::vector<std::pair<int, int>> moves = {
        {2, -1},
        {2, 1},
        {-2, -1},
        {-2, 1}};

    int row = square.at(1) - '0';
    int column = static_cast<int>(square.at(0));
    string pos;

    std::vector<string> possible_moves;
    for (auto move : moves)
    {
        pos = string(1, static_cast<char>(column + move.second)) + std::to_string(row + move.first);
        if (can_piece_move(pos))
            possible_moves.push_back(pos);
    }
    return possible_moves;
}

bool Knight::can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move) const
{
    std::vector<string> moves = get_possible_moves(from, can_piece_move);
    for (string move : moves)
    {
        if (move == to)
            return true;
    }
    return false;
}