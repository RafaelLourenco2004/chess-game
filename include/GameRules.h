#pragma once

#include <string>

#include "Board.h"
#include "King.h"
#include "Rook.h"

class Piece;
enum Color;

class GameRules
{
private:
    bool white_checked;
    bool black_checked;

    Board &board;

    std::function<bool(const string&, const string&)> can_piece_move;

    bool is_in_check(Color turn);

public:
    // GameRules(Board &board) : white_checked{false}, black_checked{false}, board{board} {}
    GameRules(Board &board);

    bool can_move(const Piece &piece, const std::string &from, const std::string &to, bool simulate_check = true);
    bool can_capture(Piece *piece, const std::string &from, const std::string &to, bool simulate_check = true);
    bool can_castle(const King *king, const Rook *piece_b, const string &king_pos, const string &rook_pos);
};