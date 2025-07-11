#pragma once

#include "Piece.h"

class Pawn : public Piece
{
private:
    bool can_push(int offset);

public:
    bool has_moved;

    Pawn() = default;
    Pawn(char type, enum Color colour);

    bool can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move) override;
    bool can_capture(const string &from, const string &to);

    ~Pawn() override = default;
};