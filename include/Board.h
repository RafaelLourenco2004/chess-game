#pragma once

#include <string>
#include <array>
#include <map>
#include <memory>

#include "Piece.h"

class Piece;

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

    std::pair<int, int> get_board_location(const string &square) const;    

public:
    Board();

    bool is_valid_square(const string &square) const;
    bool is_square_occoupied(const string &square) const;
    bool move(const string &from, const string &to);
    void display();
};