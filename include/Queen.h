#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
    Queen() = default;
    Queen(char type, enum Color colour);

    bool can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move) const override;

    ~Queen() override = default;
};