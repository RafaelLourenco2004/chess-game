#pragma once

#include "Board.h"
#include "GameRules.h"

class GameController
{
private:
    Board board;
    GameRules rules;

    bool checkmate;
    Color winner;

    bool make_move(const string &from, const string &to);

public:
    GameController() : board{}, rules{board}, checkmate{false}
    {
    }

    bool move(const string &from, const string &to);

    Color get_winner() const
    {
        return winner;
    }

    void display();
};
