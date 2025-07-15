#include <string>

#include "GameRules.h"
#include "Pawn.h"
#include "Board.h"

using std::pair;
using std::vector;

GameRules::GameRules(Board &board) : white_checked{false}, black_checked{false}, board{board}
{
    can_piece_move = [this](const string &origin, const string &dest)
    {
        if (!this->board.is_valid_square(dest) || !this->board.is_valid_square(origin))
        {
            return false;
        }

        if (this->board.is_square_occoupied(origin))
        {
            if (origin == dest)
                return true;
            return false;
        }

        return true;
    };
}

void GameRules::update_after_move(Color color)
{
    set_checked(color, false);
    Color enemy = color == WHITE ? BLACK : WHITE;
    bool is_enemy_checked = is_in_check(enemy);
    set_checked(enemy, is_enemy_checked);
}

bool GameRules::is_in_check(Color color)
{
    Color enemy = color == WHITE ? BLACK : WHITE;

    string king_square = board.get_king_location(color);
    vector<pair<string, Piece *>> pieces = board.get_pieces(enemy);
    for (const auto &piece : pieces)
    {
        bool can_take;
        Pawn *pawn = dynamic_cast<Pawn *>(piece.second);
        if (pawn != nullptr)
            can_take = pawn->can_capture(piece.first, king_square);
        else
            can_take = piece.second->can_move(piece.first, king_square, can_piece_move);

        if (can_take)
        {
            std::cout << "CHECK" << std::endl;
            return true;
        }
    }
    return false;
}

bool GameRules::can_move(const Piece &piece, const string &from, const string &to)
{
    bool is_valid = piece.can_move(from, to, can_piece_move);
    if (!is_valid)
        return false;

    board.move(from, to);
    bool is_check = is_in_check(piece.get_colour());

    if (!is_check)
    {
        update_after_move(piece.get_colour());
    }

    board.undo();
    return !is_check;
}

bool GameRules::can_capture(Piece *piece, const std::string &from, const std::string &to)
{
    bool is_valid;
    Pawn *pawn = dynamic_cast<Pawn *>(piece);
    if (pawn != nullptr)
        is_valid = pawn->can_capture(from, to);
    else
        is_valid = piece->can_move(from, to, can_piece_move);

    if (!is_valid)
        return false;

    board.take(from, to);
    bool is_check = is_in_check(piece->get_colour());

    if (!is_check)
    {
        update_after_move(piece->get_colour());
    }
    board.undo();
    return !is_check;
}

bool GameRules::can_castle(King *king, Rook *rook, const string &king_pos, const string &rook_pos)
{
    if (is_checked(king->get_colour()))
        return false;

    if (king->has_moved() || rook->has_moved())
    {
        return false;
    }

    int king_col = king_pos.at(0) - 'A';
    int rook_col = rook_pos.at(0) - 'A';
    char row = king_pos.at(1);

    int offset = rook_col > king_col ? 1 : -1;
    string square;
    for (int col = king_col + offset; col != rook_col; col += offset)
    {
        square = string(1, static_cast<char>(col + 'A')) + string(1, row);
        std::cout << square << std::endl;
        if (board.is_square_occoupied(square))
        {
            return false;
        }
    }

    board.castle(king, rook, king_pos, rook_pos);
    bool is_check = is_in_check(king->get_colour());
    if (!is_check)
    {
        update_after_move(king->get_colour());
    }
    board.undo();
    return !is_check;
}

bool GameRules::is_checkmate(Color)
{
    return false;
}
