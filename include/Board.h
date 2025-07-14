#pragma once

#include <string>
#include <array>
#include <map>
#include <memory>

#include "Piece.h"

using std::make_unique;
using std::string;
using std::unique_ptr;

class Board
{
private:
    const string BACK_ROW = "RHBQKBHR";
    const string COLUMNS = "ABCDEFGH";

    std::array<std::array<bool, 8>, 8> board = {};
    std::map<string, unique_ptr<Piece>> pieces;

    void board_init();
    void set_row(int row, enum Color colour, bool back);
    void set_piece(string pos, char type, enum Color colour);
    void set_pieces();

public:
    Board();

    std::pair<int, int> get_board_location(const string &square) const;
    bool is_valid_square(const string &square) const;
    bool is_square_occoupied(const string &square) const;
    bool exists(const string &square) const;
    void move(const string &from, const string &to);
    void take(const string &from, const string &to);
    void castle(const string &from, const string &to);
    Piece *get_piece(const string &square);
    void display();

    // bool is_type(Piece *piece) const;
    template <typename T>
    bool is_type(Piece *piece) const
    {
        return dynamic_cast<T *>(piece) != nullptr;
    }
};