#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
    bool has_moved;

    Pawn() = default;
    Pawn(char type, enum Color colour);

    bool can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move) const override;
    bool can_capture(const string &from, const string &to, std::function<bool(string)> can_piece_move);

    ~Pawn() override = default;
};