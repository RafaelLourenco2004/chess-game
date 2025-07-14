#pragma once

#include <string>
#include <array>
#include <map>
#include <vector>
#include <memory>
#include <functional>

#include "Piece.h"
#include "King.h"
#include "Rook.h"

using std::make_unique;
using std::pair;
using std::string;
using std::unique_ptr;
using std::vector;

class Board
{
private:
    const string BACK_ROW = "RHBQKBHR";
    const string COLUMNS = "ABCDEFGH";

    string white_king_square;
    string black_king_square;

    std::array<std::array<bool, 8>, 8> board = {};
    std::map<string, unique_ptr<Piece>> pieces;

    void board_init();
    void set_row(int row, enum Color colour, bool back);
    void set_piece(string pos, char type, enum Color colour);
    void set_pieces();
    void track_king(Piece *piece, const string &square);

public:
    Board();

    std::function<void()> undo;

    pair<int, int> get_board_location(const string &square) const;
    bool is_valid_square(const string &square) const;
    bool is_square_occoupied(const string &square) const;
    bool exists(const string &square) const;
    void move(const string &from, const string &to, bool undo_enabled = true);
    void take(const string &from, const string &to);
    void castle(King *king, Rook *rook, const string &king_pos, const string &rook_pos);
    Piece *get_piece(const string &square);
    vector<pair<string, Piece *>> get_pieces(Color color) const;
    void display();

    string get_king_location(Color color) const
    {
        if (color == WHITE)
            return white_king_square;
        return black_king_square;
    }

    template <typename T>
    bool is_type(Piece *piece) const
    {
        return dynamic_cast<T *>(piece) != nullptr;
    }
};