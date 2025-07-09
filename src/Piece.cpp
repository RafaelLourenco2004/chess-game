#include "Piece.h"

std::ostream &operator<<(std::ostream &os, const Piece &piece)
{
    char colour = piece.colour ? 'W' : 'B';
    os << colour << piece.type;
    return os;
}
