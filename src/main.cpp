#include <iostream>

#include "Board.h"

using std::cin;
using std::cout;
using std::endl;

bool move(Board &board)
{
    string from, to;
    cout << "Move: ";
    cin >> from >> to;

    return board.move(from, to);
}

int main()
{
    Board board{};

    board.display();

    while (move(board))
    {
        board.display();
    }
    cout << "Invalid movement" << endl;

    board.display();

    return 0;
}