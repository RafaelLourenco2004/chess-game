#pragma once

#include "Piece.h"

class King : public Piece
{
public:
    King() = default;
    King(char type, enum Color colour);

    bool can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move) override;

    ~King() override = default;
};