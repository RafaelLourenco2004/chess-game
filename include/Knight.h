#pragma once

#include <vector>
#include "Piece.h"

class Knight : public Piece
{
public:
    Knight() = default;
    Knight(char type, enum Color colour);

    bool can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move) const override;

    ~Knight() override = default;
};