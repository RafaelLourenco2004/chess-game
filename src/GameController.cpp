#include "GameController.h"
#include "King.h"
#include "Rook.h"
#include "Pawn.h"

Game_Status GameController::move(const string &from, const string &to)
{
    if (status.promotion)
    {
        status.is_move_valid = false;
        return status;
    }

    Move_Status move = make_move(from, to);
    status.is_move_valid = move.valid;
    status.promotion = move.promote;

    if (move.valid)
    {
        if (rules.is_checked(Color::WHITE) || rules.is_checked(Color::BLACK))
        {
            bool checkmate;
            if (rules.is_checked(Color::WHITE))
            {
                checkmate = rules.is_checkmate(Color::WHITE);
                if (checkmate)
                {
                    status.end_game = true;
                    status.winner = Winner::BLACK;
                }
            }
            else
            {
                checkmate = rules.is_checkmate(Color::BLACK);
                if (checkmate)
                {
                    status.end_game = true;
                    status.winner = Winner::WHITE;
                }
            }
        }
    }

    if (move.promote)
    {
        status.promotion = true;
        promotion_square = to;
    }

    return status;
}

Move_Status GameController::make_move(const string &from, const string &to)
{
    Move_Status move = {false, false};
    if (!board.is_valid_square(from) || !board.is_valid_square(to))
        return move;

    if (from == to)
        return move;

    if (!board.exists(from))
    {
        return move;
    }

    if (board.exists(to))
    {
        Piece *a = board.get_piece(from);
        Piece *b = board.get_piece(to);
        if (a->get_colour() != b->get_colour())
        {
            if (board.is_type<Pawn>(a))
            {
                char from_row = from.at(1);
                char to_row = to.at(1);

                if (from_row == to_row)
                {
                    if (rules.can_en_passant(from, to))
                    {
                        board.en_passant(from, to);
                        return {true, false};
                    }
                    return {false, false};
                }
            }

            move = rules.can_capture(a, from, to);
            if (move.valid)
            {
                board.take(from, to);
                return move;
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
                    return {true, false};
                }
            }
        }
        return {false, false};
    }

    move = rules.can_move(board.get_piece(from), from, to);
    if (move.valid)
    {
        board.move(from, to);
        return move;
        // return true;
    }

    return {false, false};
}

Game_Status GameController::promote(char type)
{
    bool success = board.promote(promotion_square, type);
    status.promotion = !success;
    return status;
}

void GameController::display()
{
    board.display();
}