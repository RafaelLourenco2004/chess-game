#pragma once

#include "Piece.h"
#include "StatefulPiece.h"

class Rook : public Piece, public StatefulPiece
{
private:
    bool can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move,
                  bool horizontal, int offset) const;

public:
    Rook() = default;
    Rook(char type, enum Color colour);

    bool can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move) const override;

    ~Rook() override = default;
};