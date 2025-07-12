#pragma once

#include "Piece.h"

class PlayerManager
{
private:
    Color turn;

public:
    PlayerManager() : turn{WHITE} {}

    Color get_turn()
    {
        return turn;
    }
};