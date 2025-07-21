#pragma once

#include <string>
#include <iostream>

#include "BoardSetup.h"

class ClassicalSetup : public BoardSetup
{
private:
    const string BACK_ROW = "RHBQKBHR";

    void set_front_row(map<string, unique_ptr<Piece>> &pieces, int row, enum Color colour);
    void set_back_row(map<string, unique_ptr<Piece>> &pieces, int row, enum Color colour);
    void set_piece(map<string, unique_ptr<Piece>> &pieces, string pos, char type, enum Color colour);

public:
    ClassicalSetup() { std::cout << "DONE CLASSIC" << std::endl; }
    void set_up(map<string, unique_ptr<Piece>> &pieces) override;
    ~ClassicalSetup() = default;
};