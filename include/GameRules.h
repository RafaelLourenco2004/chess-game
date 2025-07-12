#pragma once

#include <string>
class Piece;
class Board;

enum Color;

class GameRules
{
private:
    bool white_checked;
    bool black_checked;

    bool is_in_check(Piece &piece, const string &to, const string &from, Color turn);

public:
    GameRules() : white_checked{false}, black_checked{false} {}

    bool can_move(Piece &piece, const Board &board, const std::string &from, const std::string &to);
    bool can_capture(Piece *piece, const Board &board, const std::string &from, const std::string &to);
};