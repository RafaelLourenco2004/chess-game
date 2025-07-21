#pragma once

#include "Board.h"
#include "GameRules.h"

enum class Winner
{
    WHITE,
    BLACK,
    NONE
};

struct Game_Status
{
    bool is_move_valid;
    bool promotion;
    bool end_game;
    Winner winner;
};

class GameController
{
private:
    Board board;
    GameRules rules;

    Game_Status status;
    string promotion_square;

    Move_Status make_move(const string &from, const string &to);

public:
    GameController() : board{}, rules{board}, status{true, false, false, Winner::NONE}, promotion_square{""}
    {
    }
    // GameController() : board{}, rules{board}, checkmate{false}
    // {
    // }

    Game_Status move(const string &from, const string &to);

    // Winner get_winner() const
    // {
    //     return winner;
    // }

    Game_Status promote(char type);

    void display();
};
