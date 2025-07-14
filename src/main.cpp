#include <iostream>

#include "GameController.h"

using std::cin;
using std::cout;
using std::endl;

bool move(GameController &controller)
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
    while (move(controller))
    {
        controller.display();
    }
    cout << "Invalid movement" << endl;

    return 0;
}