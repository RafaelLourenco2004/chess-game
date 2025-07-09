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
    int column = static_cast<int>(square.at(0));
    int row = square.at(1) - '0';

    if (column < static_cast<int>(COLUMNS.front()) || column > static_cast<int>(COLUMNS.back()))
        return false;

    if (row < 1 || row > 8)
        return false;

    return true;
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

bool Board::move(const string &from, const string &to)
{
    if (!is_valid_square(from) || !is_valid_square(to))
    {
        std::cout << "Invalid Square" << std::endl;
        return false;
    }

    if (is_square_occoupied(to))
    {
        std::cout << "Occupied" << std::endl;
        return false;
    }

    if (pieces.find(from) == pieces.end())
    {
        std::cout << "Not Found" << std::endl;
        return false;
    }

    if (!GameRules::can_move((*pieces[from].get()), *this, from, to))
    {
        std::cout << "Can not move" << std::endl;
        return false;
    }

    std::pair<int, int> from_loc = get_board_location(from);
    std::pair<int, int> to_loc = get_board_location(to);

    board[from_loc.first][from_loc.second] = false;
    board[to_loc.first][to_loc.second] = true;

    auto piece = pieces.find(from);
    pieces[to] = std::move(piece->second);
    pieces.erase(piece);
    return true;
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