// FCAI _ OOP Programming _ 2023 _ Assignment 3
// Program Name: Game App
// Last Modification Date: 16/12/2023
// Author1 name and ID: Abdelrahman Ahmed Lotfy   20220474   Obidah05@gmail.com
// Author2 name and ID: Ahmed Hossam ElAlfy       20220016   ahalfy2005@gmail.com
// Author3 name and ID: Alshimaa Mohamed Abdo     20220067   mshmsh1582004@gmail.com
// Section:   S22
// Teaching Assistant:   Eng/ Rana AbdelKader
// Purpose: An app that consists of 4 different games and let the user choose
// which game he wants to play and if he wants to play against another player or
// a random computer player.

#include <iostream>
#include"GameManager.cpp"
#include"BoardGame_Classes.h"
#include"RandomPlayer.cpp"
#include"X_O_Board.cpp"
using namespace std;

int main() {
    cout<<"Welcome to our game app\n";
    cout<<"Please choose the number of the game you want to play:\n"
          "1- X_O\n"
          "2- Pyramic Tic_Tac_Toe\n"
          "3- Four_in_a_row(Connect 4)\n"
          "4- 5x5 Tic_Tac_Toe\n";
    int game;
    cin>>game;
    if(game==1){
        int choice;
        Player* players[2];
        players[0] = new Player(1, 'x');
        cout << "Welcome to FCAI X_O Game. :)\n";
        cout << "Press 1 if you want to play with computer, any other integer if you want to play against your friend: ";
        cin >> choice;
        if (choice != 1)
            players[1] = new Player( 2, 'o');
        else
            //Player pointer points to child
            players[1] = new RandomPlayer('o', 2);

        GameManager X_O_game (new X_O_Board, players);
        X_O_game.run();
        system ("pause");
    }
    else if(game==2){
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
    else if (game==3){
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
    else if(game ==4){
        cout << "5 x 5\n";
        int choice;
        Player* players[2];
        players[0] = new Player5x5 (1, 'x');

        cout << "Welcome to FCAI X-O 5x5 Game. :)\n";
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
    else{
        cout<<"Sorry that is not an option.";
    }
}
