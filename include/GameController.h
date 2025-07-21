#pragma once

#include "Board.h"
#include "GameRules.h"
#include "BoardSetup.h"
#include "ClassicalSetup.h"

enum Setup
{
    CLASSIC
};

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

    Color turn;
    string promotion_square;

    unique_ptr<BoardSetup> make_setup(Setup set_up);
    Move_Status make_move(const string &from, const string &to);

    void change_turn();

public:
    GameController(Setup set_up);

    Game_Status move(const string &from, const string &to);
    Game_Status promote(char type);

    void display();
};
