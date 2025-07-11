#pragma once

#include "Piece.h"

class King : public Piece
{
private:
    bool has_moved;

public:
    King() = default;
    King(char type, enum Color colour);

    bool can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move) override;

    bool has_king_moved()
    {
        return has_moved;
    }
    ~King() override = default;
};