#pragma once

#include <string>
#include <array>
#include <map>
#include <vector>
#include <memory>
#include <functional>

#include "BoardSetup.h"
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
    unique_ptr<BoardSetup> setup;

    const string COLUMNS = "ABCDEFGH";

    string wk_square;
    string bk_square;

    std::array<std::array<bool, 8>, 8> board = {};
    std::map<string, unique_ptr<Piece>> pieces;

    void board_init();
    void track_king(Piece *piece, const string &square);

public:
    Board(unique_ptr<BoardSetup> set_up);

    std::function<void()> undo;

    pair<int, int> get_board_location(const string &square) const;
    bool is_valid_square(const string &square) const;
    bool is_square_occoupied(const string &square) const;
    bool exists(const string &square) const;
    void move(const string &from, const string &to, bool undo_enabled = true);
    void take(const string &from, const string &to);
    void castle(King *king, Rook *rook, const string &king_pos, const string &rook_pos);
    void en_passant(const string &taker_square, const string &target_square);
    bool promote(string square, char type);
    Piece *get_piece(const string &square);
    vector<pair<string, Piece *>> get_pieces(Color color) const;
    void display();

    string get_king_location(Color color) const
    {
        if (color == WHITE)
            return wk_square;
        return bk_square;
    }

    template <typename T>
    bool is_type(Piece *piece) const
    {
        return dynamic_cast<T *>(piece) != nullptr;
    }
};