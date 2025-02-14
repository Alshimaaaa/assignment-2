// Class definition for XO_App class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1

#include <iostream>

#include "../original/GameManager.cpp"
#include "../original/Player.cpp"

#include"BoardGame_Classes5x5.hpp"
#include "X_O_Board5x5.cpp"
#include "Player5x5.cpp"
#include "RandomPlayer5x5.cpp"

using namespace std;

int main() {
    cout << "5 x 5\n";
    int choice;
    Player* players[2];
    players[0] = new Player5x5 (1, 'x');

    cout << "Welcome to FCAI X-O Game. :)\n";
    cout << "Important Disclaimer: For this game, only the symbol x or o can be declared as a winner, player names being declared as winners is meaningless" << endl;        
    cout << "Press 1 if you want to play with computer: ";
    cin >> choice;
    if (choice != 1)
        players[1] = new Player5x5 (2, 'o');
    else
        //Player pointer points to child
        players[1] = new RandomPlayer ('o', 5);

    GameManager x_o_game (new Board5x5(), players);
    x_o_game.run();
    system ("pause");
}
