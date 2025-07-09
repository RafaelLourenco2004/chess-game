#include "King.h"

King::King(char type, enum Color colour) : Piece(type, colour)
{
}

bool King::can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move) const
{
    return true;
}