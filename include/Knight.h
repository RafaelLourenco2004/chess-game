#pragma once

#include <vector>
#include "Piece.h"

class Knight : public Piece
{
private:
    std::vector<string> get_possible_moves(const string &square, std::function<bool(string)> can_piece_move) const;

public:
    Knight() = default;
    Knight(char type, enum Color colour);

    bool can_move(const string &from, const string &to, std::function<bool(string)> can_piece_move) const override;

    ~Knight() override = default;
};