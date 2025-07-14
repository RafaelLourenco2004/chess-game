#pragma once

#include <string>

#include "Board.h"

class Piece;
enum Color;

class GameRules
{
private:
    bool white_checked;
    bool black_checked;

    const Board &board;

    // bool is_in_check(Piece &piece, const string &to, const string &from, Color turn);

public:
    GameRules(Board &board) : white_checked{false}, black_checked{false}, board{board} {}

    bool can_move(Piece &piece, const std::string &from, const std::string &to);
    bool can_capture(Piece *piece, const std::string &from, const std::string &to);
    bool can_castle(Piece *piece_a, Piece *piece_b, const string &from, const string &to);
};