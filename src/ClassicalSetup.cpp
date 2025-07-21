#include "ClassicalSetup.h"
#include "Pieces.h"

using std::make_unique;

void ClassicalSetup::set_piece(map<string, unique_ptr<Piece>> &pieces, string pos, char type, enum Color colour)
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

void ClassicalSetup::set_back_row(map<string, unique_ptr<Piece>> &pieces, int row, enum Color colour)
{
    string pos;
    for (int col = 0; col < 8; col++)
    {
        pos = COLUMNS.at(col) + std::to_string(row);
        set_piece(pieces, pos, BACK_ROW.at(col), colour);
    }
}

void ClassicalSetup::set_front_row(map<string, unique_ptr<Piece>> &pieces, int row, enum Color colour)
{
    string pos;
    for (int col = 0; col < 8; col++)
    {
        pos = COLUMNS.at(col) + std::to_string(row);
        pieces[pos] = make_unique<Pawn>('P', colour);
    }
}

void ClassicalSetup::set_up(map<string, unique_ptr<Piece>> &pieces)
{
    set_back_row(pieces, 1, WHITE);
    set_back_row(pieces, 8, BLACK);
    set_front_row(pieces, 2, WHITE);
    set_front_row(pieces, 7, BLACK);
}