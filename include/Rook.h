#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
    Rook() = default;
    Rook(char type, enum Color colour);

    bool can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move) const override;

    ~Rook() override = default;
};