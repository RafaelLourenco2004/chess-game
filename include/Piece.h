#pragma once

#include <iostream>
#include <ostream>
#include <functional>

using std::string;

enum Color
{
    BLACK,
    WHITE
};

class Piece
{
    friend std::ostream &operator<<(std::ostream &os, const Piece &piece);

protected:
    char type;
    enum Color colour;

public:
    Piece() = default;
    Piece(char type, enum Color colour) : type{type}, colour{colour} {};

    virtual bool can_move(const string &from, const string &to,
                          std::function<bool(string, string)> can_piece_move) const = 0;
    virtual ~Piece() = default;

    char get_type() const
    {
        return type;
    }

    enum Color get_colour() const
    {
        return colour;
    }
};