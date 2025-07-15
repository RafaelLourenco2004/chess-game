#include "GameController.h"
#include "King.h"
#include "Rook.h"

bool GameController::move(const string &from, const string &to)
{
    bool moved = make_move(from, to);
    if (moved)
    {
        if (rules.is_checked(WHITE) || rules.is_checked(BLACK))
        {
            if (rules.is_checked(WHITE))
            {
                checkmate = rules.is_checkmate(WHITE);
                if (checkmate)
                    winner = BLACK;
            }
            else
            {
                checkmate = rules.is_checkmate(BLACK);
                if (checkmate)
                    winner = WHITE;
            }
        }
        return true;
    }
    return false;
}

bool GameController::make_move(const string &from, const string &to)
{
    if (!board.is_valid_square(from) || !board.is_valid_square(to))
        return false;

    if (from == to)
        return false;

    if (!board.exists(from))
    {
        return false;
    }
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
                King *king;
                Rook *rook;
                string king_pos;
                string rook_pos;
                if (board.is_type<King>(a))
                {
                    king = dynamic_cast<King *>(a);
                    rook = dynamic_cast<Rook *>(b);
                    king_pos = from;
                    rook_pos = to;
                }
                else
                {
                    king = dynamic_cast<King *>(b);
                    rook = dynamic_cast<Rook *>(a);
                    king_pos = to;
                    rook_pos = from;
                }

                if (rules.can_castle(king, rook, king_pos, rook_pos))
                {
                    board.castle(king, rook, king_pos, rook_pos);
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