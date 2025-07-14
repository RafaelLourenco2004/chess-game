#include <iostream>

#include "Pieces.h"
#include "Board.h"
#include "StatefulPiece.h"

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

Board::Board() : undo{[] {}}, white_king_square{"E1"}, black_king_square{"E8"}
{
    board_init();
    set_pieces();
}

vector<pair<string, Piece *>> Board::get_pieces(Color color) const
{
    std::vector<pair<string, Piece *>> pieces_ptr;
    for (const auto &piece : pieces)
    {
        if (piece.second->get_colour() == color)
            pieces_ptr.push_back(std::make_pair(piece.first, piece.second.get()));
    }
    return pieces_ptr;
}

void Board::track_king(Piece *piece, const string &square)
{
    if (!is_type<King>(piece))
        return;

    if (piece->get_colour() == WHITE)
        white_king_square = square;
    else
        black_king_square = square;
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

bool Board::exists(const string &square) const
{
    return pieces.find(square) != pieces.end();
}

Piece *Board::get_piece(const string &square)
{
    return pieces[square].get();
}

void Board::move(const string &from, const string &to, bool undo_enabled)
{
    std::pair<int, int> from_loc = get_board_location(from);
    std::pair<int, int> to_loc = get_board_location(to);

    board[from_loc.first][from_loc.second] = false;
    board[to_loc.first][to_loc.second] = true;

    auto piece = pieces.find(from);

    track_king(piece->second.get(), to);

    Piece *stl_piece = piece->second.get();
    if (is_type<StatefulPiece>(stl_piece) && undo_enabled)
    {
        StatefulPiece *stf_piece = dynamic_cast<StatefulPiece *>(stl_piece);

        bool moved = stf_piece->has_moved();
        if (!moved)
            stf_piece->set_moved(true);

        undo = [=]()
        {
            this->move(to, from, false);
            stf_piece->set_moved(moved);
        };
    }
    else if (undo_enabled)
    {
        undo = [=]()
        {
            this->move(to, from, false);
        };
    }

    pieces[to] = std::move(piece->second);
    pieces.erase(piece);
}

void Board::take(const string &from, const string &to)
{
    std::pair<int, int> from_loc = get_board_location(from);

    board[from_loc.first][from_loc.second] = false;

    auto taken_piece_it = pieces.find(to);
    unique_ptr<Piece> taken_piece_ptr = std::move(taken_piece_it->second);
    Piece *piece = taken_piece_ptr.release();
    pieces.erase(taken_piece_it);

    auto taker = pieces.find(from);

    track_king(taker->second.get(), to);

    pieces[to] = std::move(taker->second);
    pieces.erase(taker);

    undo = [=]()
    {
        this->pieces[from] = std::move(this->pieces[to]);
        this->track_king(this->pieces[to].get(), from);
        this->pieces[to] = std::unique_ptr<Piece>(piece);

        this->board[from_loc.first][from_loc.second] = true;
    };
}

void Board::castle(King *king, Rook *rook, const string &king_pos, const string &rook_pos)
{
    int king_col = static_cast<int>(king_pos.at(0));
    int rook_col = static_cast<int>(rook_pos.at(0));

    int offset = rook_col - king_col;

    int row = king_pos.at(1) - '0';
    rook_col = offset > 0 ? king_col + 1 : king_col - 1;
    king_col += offset > 0 ? 2 : -2;

    string new_king_pos = string(1, static_cast<char>(king_col)) + std::to_string(row);
    string new_rook_pos = string(1, static_cast<char>(rook_col)) + std::to_string(row);
    move(king_pos, new_king_pos);
    move(rook_pos, new_rook_pos);

    king->set_moved(true);
    rook->set_moved(true);

    track_king(king, king_pos);

    undo = [=]()
    {
        this->move(new_king_pos, king_pos, false);
        this->move(new_rook_pos, rook_pos, false);
        king->set_moved(false);
        rook->set_moved(false);
    };
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