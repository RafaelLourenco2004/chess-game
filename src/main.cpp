#include <iostream>

#include "GameController.h"

using std::cin;
using std::cout;
using std::endl;

Game_Status promote(GameController &controller)
{
    char type;
    bool promoted = true;

    Game_Status status;
    while (promoted)
    {
        cout << "\nSelect a piece : " << endl;
        cout << "\t" << "R - ROOK" << endl;
        cout << "\t" << "H - KIGHT" << endl;
        cout << "\t" << "B - BISHOP" << endl;
        cout << "\t" << "Q - QUEEN" << endl;
        cin >> type;
        status = controller.promote(type);
        if (status.promotion)
        {
            cout << "Invalid option. Try again" << endl;
        }
        promoted = status.promotion;
    }
    return status;
}

Game_Status move(GameController &controller)
{
    string from, to;
    cout << "Move: ";
    cin >> from >> to;

    return controller.move(from, to);
}

int main()
{
    GameController controller;

    controller.display();

    Game_Status status;
    bool endgame = false;
    while (!endgame)
    {
        status = move(controller);

        if (!status.is_move_valid)
        {
            cout << "Invalid movement" << endl;
            continue;
        }

        if (status.promotion)
        {
            promote(controller);
        }

        endgame = status.end_game;
        controller.display();
    }

    return 0;
}