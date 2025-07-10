#pragma once

#include "Piece.h"

class Queen : public Piece
{
private:
    bool can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move,
                  std::pair<int, int> offset) const;

    bool can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move,
                  bool horizontal, int offset) const;

public:
    Queen() = default;
    Queen(char type, enum Color colour);

    bool can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move) override;

    ~Queen() override = default;
};