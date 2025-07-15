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

    std::function<bool(const string &, const string &)> can_piece_move;

    bool is_in_check(Color turn);
    void update_after_move(Color color); 

    void set_checked(Color color, bool checked)
    {
        if (color == WHITE)
            white_checked = checked;
        else
            black_checked = checked;
    }

public:
    // GameRules(Board &board) : white_checked{false}, black_checked{false}, board{board} {}
    GameRules(Board &board);

    bool can_move(const Piece &piece, const std::string &from, const std::string &to);
    bool can_capture(Piece *piece, const std::string &from, const std::string &to);
    bool can_castle(King *king, Rook *piece_b, const string &king_pos, const string &rook_pos);

    bool is_checkmate(Color);

    bool is_checked(Color color) const
    {
        if (color == WHITE)
            return white_checked;
        return black_checked;
    }
};