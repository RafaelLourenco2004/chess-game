#pragma once

#include "Piece.h"
#include "StatefulPiece.h"

class King : public Piece, public StatefulPiece
{
public:
    King() = default;
    King(char type, enum Color colour);

    bool can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move) const override;
    
    ~King() override = default;
};