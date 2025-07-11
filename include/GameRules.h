#pragma once

#include <string>

class Piece;
class Board;

class GameRules
{
public:
    static bool can_move(Piece &piece, const Board &board, const std::string &from, const std::string &to);
    static bool can_capture(Piece *piece, const Board &board, const std::string &from, const std::string &to);
    
};