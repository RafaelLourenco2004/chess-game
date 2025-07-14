#pragma once

#include "Piece.h"

class Bishop : public Piece
{
private:
    bool can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move,
                  std::pair<int, int> offset) const;

public:
    Bishop() = default;
    Bishop(char type, enum Color colour);

    bool can_move(const string &from, const string &to, std::function<bool(string, string)> can_piece_move) const override;

    ~Bishop() override = default;
};