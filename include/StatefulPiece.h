#pragma once

class StatefulPiece
{
private:
    bool moved;

public:
    StatefulPiece(): moved{false}{}

    bool has_moved() const
    {
        return moved;
    }

    void set_moved(bool moved)
    {
        this->moved = moved;
    }

    virtual ~StatefulPiece() = default;
};