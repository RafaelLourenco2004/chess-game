#pragma once

#include "Piece.h"
#include "StatefulPiece.h"

class Pawn : public Piece, public StatefulPiece
{
private:
    bool can_push(int offset) const;

public:
    Pawn() = default;
    Pawn(char type, enum Color colour);

    bool can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move) const override;
    bool can_capture(const string &from, const string &to);

    ~Pawn() override = default;
};