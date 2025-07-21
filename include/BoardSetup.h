#pragma once

#include <map>
#include <string>
#include <memory>

#include "Piece.h"

using std::map;
using std::string;
using std::unique_ptr;

class BoardSetup
{
protected:
    const string COLUMNS = "ABCDEFGH";

public:
    virtual void set_up(map<string, unique_ptr<Piece>> &pieces) = 0;
    virtual ~BoardSetup() = default;
};