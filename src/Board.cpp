#include <iostream>

#include "Pieces.h"
#include "Board.h"
#include "GameRules.h"

void Board::board_init()
{
    for (int line : {0, 1, 6, 7})
    {
        for (int i = 0; i < 8; i++)
        {
            board[line][i] = true;
        }
    }
}

void Board::set_piece(string pos, char type, enum Color colour)
{
    unique_ptr<Piece> piece;
    switch (type)
    {
    case 'R':
        piece = make_unique<Rook>('R', colour);
        break;
    case 'H':
        piece = make_unique<Knight>('H', colour);
        break;
    case 'B':
        piece = make_unique<Bishop>('B', colour);
        break;
    case 'Q':
        piece = make_unique<Queen>('Q', colour);
        break;
    case 'K':
        piece = make_unique<King>('K', colour);
        break;
    default:
        break;
    }
    pieces[pos] = std::move(piece);
}

void Board::set_row(int row, enum Color colour, bool back)
{
    string pos;
    for (int col = 0; col < 8; col++)
    {
        pos = COLUMNS.at(col) + std::to_string(row);
        if (back)
            set_piece(pos, BACK_ROW.at(col), colour);
        else
            pieces[pos] = make_unique<Pawn>('P', colour);
    }
}

void Board::set_pieces()
{
    set_row(1, WHITE, true);
    set_row(2, WHITE, false);
    set_row(8, BLACK, true);
    set_row(7, BLACK, false);
}

Board::Board()
{
    board_init();
    set_pieces();
}

bool Board::is_valid_square(const string &square) const
{
    char column = square.at(0);
    char row = square.at(1);

    if (column < COLUMNS.front() || column > COLUMNS.back())
        return false;

    if (row < '1' || row > '8')
        return false;

    return true;
}

void Board::move_on_board(const string &from, const string &to)
{
    std::pair<int, int> from_loc = get_board_location(from);
    std::pair<int, int> to_loc = get_board_location(to);

    board[from_loc.first][from_loc.second] = false;
    board[to_loc.first][to_loc.second] = true;

    auto piece = pieces.find(from);
    pieces[to] = std::move(piece->second);
    pieces.erase(piece);
}

std::pair<int, int> Board::get_board_location(const string &square) const
{
    int col = COLUMNS.find(square.at(0));
    int row = (square.at(1) - '0') - 1;
    return std::make_pair(row, col);
}

bool Board::is_square_occoupied(const string &square) const
{
    std::pair<int, int> coord = get_board_location(square);
    return board[coord.first][coord.second];
}

template <typename T>
bool Board::is_type(const unique_ptr<Piece> &piece)
{
    return dynamic_cast<T *>(piece.get()) != nullptr;
}

bool Board::move_piece(const string &from, const string &to)
{
    if (!GameRules::can_move((*pieces[from].get()), *this, from, to))
    {
        std::cout << "Can not move" << std::endl;
        return false;
    }

    move_on_board(from, to);
    return true;
}

bool Board::castle(unique_ptr<Piece> &piece_a, unique_ptr<Piece> &piece_b, const string &from, const string &to)
{
    King *king = nullptr;
    Rook *rook = nullptr;
    string king_pos;
    string rook_pos;
    if (is_type<King>(piece_a))
    {
        king = dynamic_cast<King *>(piece_a.get());
        rook = dynamic_cast<Rook *>(piece_b.get());
        king_pos = from;
        rook_pos = to;
    }
    else
    {
        king = dynamic_cast<King *>(piece_b.get());
        rook = dynamic_cast<Rook *>(piece_a.get());
        king_pos = to;
        rook_pos = from;
    }

    if (king->has_king_moved() || rook->has_rook_moved())
    {
        return false;
    }

    int king_col = king_pos.at(0) - 'A';
    int rook_col = rook_pos.at(0) - 'A';
    int row = (king_pos.at(1) - '0') - 1;

    int offset = rook_col > king_col ? 1 : -1;
    for (int col = king_col + offset; col != rook_col; col += offset)
    {
        if (board[row][col])
        {
            return false;
        }
    }

    if (offset == 1)
    {
        move_on_board(king_pos, string(1, static_cast<char>('A' + king_col + 2)) + std::to_string(row + 1));
        move_on_board(rook_pos, string(1, static_cast<char>('A' + king_col + 1)) + std::to_string(row + 1));
    }
    else
    {
        move_on_board(king_pos, string(1, static_cast<char>('A' + king_col - 2)) + std::to_string(row + 1));
        move_on_board(rook_pos, string(1, static_cast<char>('A' + king_col - 1)) + std::to_string(row + 1));
    }
    return true;
}

bool Board::take(const string &from, const string &to)
{
    // if (!GameRules::can_move((*pieces[from].get()), *this, from, to))
    // {
    //     std::cout << "Can not move" << std::endl;
    //     return false;
    // }
    if (!GameRules::can_capture(pieces[from].get(), *this, from, to))
    {
        std::cout << "Can not move" << std::endl;
        return false;
    }

    std::pair<int, int> from_loc = get_board_location(from);
    std::pair<int, int> to_loc = get_board_location(to);

    board[from_loc.first][from_loc.second] = false;
    board[to_loc.first][to_loc.second] = true;

    auto taken_piece = pieces.find(to);
    pieces.erase(taken_piece);
    auto taker = pieces.find(from);
    pieces[to] = std::move(taker->second);
    pieces.erase(taker);
    return true;
}

bool Board::move(const string &from, const string &to)
{
    if (!is_valid_square(from) || !is_valid_square(to))
    {
        std::cout << "Invalid Square" << std::endl;
        return false;
    }

    if (from == to)
        return false;

    auto from_piece = pieces.find(from);
    if (from_piece == pieces.end())
        return false;

    auto to_piece = pieces.find(to);
    if (to_piece == pieces.end())
        return move_piece(from, to);

    unique_ptr<Piece> &piece_a = from_piece->second;
    unique_ptr<Piece> &piece_b = to_piece->second;
    if (piece_a->get_colour() == piece_b->get_colour())
    {
        if ((is_type<Rook>(piece_a) && is_type<King>(piece_b)) || (is_type<Rook>(piece_b) && is_type<King>(piece_a)))
        {
            return castle(piece_a, piece_b, from, to);
        }
        return false;
    }

    return take(from, to);
}

void Board::display()
{
    string pos;
    for (int i = 7; i >= 0; i--)
    {
        std::cout << i + 1 << " ";
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j])
            {
                pos = COLUMNS.at(j) + std::to_string(i + 1);
                std::cout << *(pieces[pos].get()) << " ";
            }
            else
                std::cout << "-- ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 8; i++)
    {
        std::cout << "  " << COLUMNS.at(i);
    }
    std::cout << std::endl;
}