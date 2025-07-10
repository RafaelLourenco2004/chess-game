#pragma once

#include "Piece.h"

class Rook : public Piece
{
private:
    bool can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move,
                  bool horizontal, int offset) const;

public:
    Rook() = default;
    Rook(char type, enum Color colour);

    bool can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move) override;

    ~Rook() override = default;
};