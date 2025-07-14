#include "GameController.h"
#include "King.h"
#include "Rook.h"

bool GameController::move(const string &from, const string &to)
{
    if (!board.is_valid_square(from) || !board.is_valid_square(to))
        return false;

    if (from == to)
        return false;

    if (!board.exists(from))
        return false;

    if (board.exists(to))
    {
        Piece *a = board.get_piece(from);
        Piece *b = board.get_piece(to);
        if (a->get_colour() != b->get_colour())
        {
            if (rules.can_capture(a, from, to))
            {
                board.take(from, to);
                return true;
            }
        }
        else
        {
            if ((board.is_type<King>(a) && board.is_type<Rook>(b)) || (board.is_type<King>(b) && board.is_type<Rook>(a)))
            {
                if (rules.can_castle(a, b, from, to))
                {
                    board.castle(from, to);
                    return true;
                }
            }
        }
        return false;
    }

    if (rules.can_move(*board.get_piece(from), from, to))
    {
        board.move(from, to);
        return true;
    }

    return false;
}

void GameController::display()
{
    board.display();
}