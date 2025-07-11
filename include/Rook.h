#pragma once

#include "Piece.h"

class Rook : public Piece
{
private:
    bool has_moved;

    bool can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move,
                  bool horizontal, int offset);

public:
    Rook() = default;
    Rook(char type, enum Color colour);

    bool has_rook_moved()
    {
        return has_moved;
    }

    bool can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move) override;

    ~Rook() override = default;
};