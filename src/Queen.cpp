#include "Queen.h"

Queen::Queen(char type, enum Color colour): Piece(type, colour)
{
}

bool Queen::can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move) const
{
    return true;
}