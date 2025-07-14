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

bool GameRules::is_in_check(Color color)
{
    Color enemy = color == WHITE ? BLACK : WHITE;

    string king_square = board.get_king_location(color);
    vector<pair<string, Piece *>> pieces = board.get_pieces(enemy);
    for (const auto &piece : pieces)
    {
        if (can_capture(piece.second, piece.first, king_square, false))
        {
            std::cout << "CHECK" << std::endl;
            return true;
        }
    }
    return false;
}

bool GameRules::can_move(const Piece &piece, const string &from, const string &to, bool simulate_check)
{
    bool is_valid = piece.can_move(from, to, can_piece_move);
    if (!is_valid)
        return false;

    board.move(from, to);
    bool is_check = is_in_check(piece.get_colour());
    board.undo();

    return !is_check;
}

bool GameRules::can_capture(Piece *piece, const std::string &from, const std::string &to, bool simulate_check)
{
    bool is_valid;
    Pawn *pawn = dynamic_cast<Pawn *>(piece);
    if (pawn != nullptr)
        is_valid = pawn->can_capture(from, to);
    else
        is_valid = piece->can_move(from, to, can_piece_move);

    if (!is_valid)
        return false;

    if (!simulate_check)
        return is_valid;

    board.take(from, to);
    bool is_check = is_in_check(piece->get_colour());
    board.undo();
    return !is_check;
}

bool GameRules::can_castle(const King *king, const Rook *rook, const string &king_pos, const string &rook_pos)
{
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
    return true;
}
