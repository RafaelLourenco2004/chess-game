#pragma once

#include "Board.h"
#include "GameRules.h"

class GameController
{
private:
    Board board;
    GameRules rules;

public:
    GameController() : board{}, rules{board}
    {
    }

    bool move(const string &from, const string &to);
    void display();
};
