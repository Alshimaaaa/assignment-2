// Class definition for XO_App class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1

#include <iostream>

#include "../original/GameManager.cpp"
#include "../original/Player.cpp"

#include "BoardGame_Classes_four_in_a_row.h"
#include "X_O_Board_four_in_a_row.cpp"
#include "Player_four_in_a_row.cpp"
#include "RandomPlayer_four_in_a_row.cpp"

using namespace std;

int main() {
    int choice;
    Player* players[2];
    players[0] = new Connect4_Player('x', 1, 'x');

    cout << "Welcome to FCAI Connect 4 Game. :)\n";
    cout << "Press 1 if you want to play with computer, any other integer if you want to play against your friend: ";
    cin >> choice;
    if (choice != 1)
        players[1] = new Connect4_Player('o', 2, 'o');
    else
        //Player pointer points to child
        players[1] = new Connect4_RandomPlayer('o', 6);

    GameManager Connect4_game (new Connect4_Board, players);
    Connect4_game.run();
    system ("pause");
}
