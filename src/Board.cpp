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

Board::Board(unique_ptr<BoardSetup> setup) : setup{std::move(setup)}, undo{[] {}}, wk_square{"E1"}, bk_square{"E8"}
{
    board_init();
    this->setup->set_up(pieces);
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
        wk_square = square;
    else
        bk_square = square;
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

    undo = [=]()
    {
        this->move(new_king_pos, king_pos, false);
        this->move(new_rook_pos, rook_pos, false);
        king->set_moved(false);
        rook->set_moved(false);
    };
}

void Board::en_passant(const string &taker_square, const string &target_square)
{
    Piece *taker = get_piece(taker_square);
    int dest_row_offset = taker->get_colour() == WHITE ? 1 : -1;
    char dest_row = (taker_square.at(1)) + dest_row_offset;

    string dest_square = string(1, taker_square.at(0)) + string(1, dest_row);
    move(taker_square, dest_square, false);

    auto target_it = pieces.find(target_square);
    unique_ptr<Piece> target_ptr = std::move(target_it->second);
    Piece *piece = target_ptr.release();
    pieces.erase(target_it);

    pair<int, int> target_loc = get_board_location(target_square);
    board[target_loc.first][target_loc.second] = false;

    undo = [=]()
    {
        this->move(dest_square, taker_square, false);
        this->pieces[target_square] = std::unique_ptr<Piece>(piece);
        this->board[target_loc.first][target_loc.second] = true;
    };
}

bool Board::promote(string square, char type)
{
    string promotion_pieces = "RHBQ";
    if (promotion_pieces.find(type) == -1)
        return false;

    auto piece = pieces.find(square);
    Color color = piece->second->get_colour();

    pieces.erase(piece);

    switch (type)
    {
    case 'R':
        pieces[square] = make_unique<Rook>(type, color);
        break;
    case 'H':
        pieces[square] = make_unique<Knight>(type, color);
        break;
    case 'B':
        pieces[square] = make_unique<Bishop>(type, color);
        break;
    case 'Q':
        pieces[square] = make_unique<Queen>(type, color);
        break;
    default:
        return false;
    }

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