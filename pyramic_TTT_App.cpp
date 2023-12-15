// File name:   pyramic_TTT_app.cpp
// Purpose:     the main app for using the classes for the pyramic version of the tic tac toe game.
// Author(s):   Ahmed Hossam Samir ElAlfy        
// ID(s):       20220016
// Section:     S22
// Date:        13 December 2023

#include <iostream>

#include "pyramic_TTT.hpp"
#include "pyramic_TTT_Board.cpp"
#include "pyramic_TTT_Player.cpp"

#include "BoardGame_Classes.hpp"
#include "GameManager.cpp"
#include "Player.cpp"
#include "RandomPlayer.cpp"

using namespace std;

int main () {
    //an option is added where every player can choose the symbol to use.

    Player* players[2];

    //set the matters of the first player
    cout << "Welcome to FCAI X-O pyramic Game. :)\n";
    cout << "enter the symbol that you want to use: ";
    char symbol1;
    cin >> symbol1;
    players[0] = new Pyramic_TTT_Player (1, symbol1);

    //choose wether to play with another human player or with the computer.
    cout << "Press 1 if you want to play with the computer, or any other number if you have someone to play with!: ";
    int choice;
    cin >> choice;

    if (choice != 1)
    {
        //set the matters of the other human player
        cout << "enter the symbol that your opponent wants to use: ";
        char symbol2;
        cin >> symbol2;
        players[1] = new Pyramic_TTT_Player (2, symbol2);
    }
    else
    {
        //create a computer player
        //5 is passed to the dimension parameter, as it's the bigger dimension in the board's rectangle (the generated random numbers will be checked by Pyramic_TTT_Board::update_board() function).
        players[1] = new RandomPlayer ('O', 5);
    }

    //run the game
    GameManager Pyramic_TTT_game (new Pyramic_TTT_Board(), players);
    Pyramic_TTT_game.run();
    system ("pause");
}