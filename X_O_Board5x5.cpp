// Class definition for X_O_Board class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1
#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include "../include/BoardGame_Classes5x5.hpp"
using namespace std;

// Set the board
X_O_Board::X_O_Board () {
   n_rows = n_cols = 3;
   board = new char*[n_rows];
   for (int i = 0; i < n_rows; i++) {
      board [i] = new char[n_cols];
      for (int j = 0; j < n_cols; j++)
         board[i][j] = 0;
   }
}

// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool X_O_Board::update_board (int x, int y, char mark){
   // Only update if move is valid
   if (!(x < 0 || x > 2 || y < 0 || y > 2) && (board[x][y] == 0)) {
      board[x][y] = toupper(mark);
      n_moves++;
      return true;
   }
   else
      return false;
}

// Display the board and the pieces on it
void X_O_Board::display_board() {
   for (int i: {0,1,2}) {
      cout << "\n| ";
      for (int j: {0,1,2}) {
         cout << "(" << i << "," << j << ")";
         cout << setw(2) << board [i][j] << " |";
      }
      cout << "\n-----------------------------";
   }
   cout << endl;
}

// Returns true if there is any winner
// either X or O
// Written in a complex way. DO NOT DO LIKE THIS.
bool X_O_Board::is_winner() {
    char row_win[3], col_win[3], diag_win[2];
    for (int i:{0,1,2}) {
        row_win[i] = board[i][0] & board[i][1] & board[i][2];
        col_win[i] = board[0][i] & board[1][i] & board[2][i];
    }
    diag_win[0] = board[0][0] & board[1][1] & board[2][2];
    diag_win[1] = board[2][0] & board[1][1] & board[0][2];

    for (int i:{0,1,2}) {
        if ( (row_win[i] && (row_win[i] == board[i][0])) ||
             (col_win[i] && (col_win[i] == board[0][i])) )
            {return true;}
    }
    if ((diag_win[0] && diag_win[0] == board[1][1]) ||
        (diag_win[1] && diag_win[1] == board[1][1]))
        {return true;}
    return false;
}

// Return true if 9 moves are done and no winner
bool X_O_Board::is_draw() {
    return (n_moves == 9 && !is_winner());
}

bool X_O_Board::game_is_over () {
    return n_moves >= 9;
}

Board5x5::Board5x5()
{
    x_wins = 0;
    o_wins = 0;
    n_rows = n_cols = 5;
   board = new char*[n_rows];
   for (int i = 0; i < n_rows; i++) {
      board [i] = new char[n_cols];
      for (int j = 0; j < n_cols; j++)
         board[i][j] = 0;
    }
}

bool Board5x5::update_board(int x, int y, char mark)
{
    //checks boundaries
    if (!(x < 0 || x > 4 || y < 0 || y > 4) && (board[x][y] == 0)) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    else
        return false;
}

void Board5x5::display_board()
{
     for (int i: {0,1,2,3,4}) {
      cout << "\n| ";
      for (int j: {0,1,2,3,4}) {
         cout << "(" << i << "," << j << ")";
         cout << setw(2) << board [i][j] << " |";
      }
      cout << "\n-----------------------------";
   }
   cout << endl;
}

bool Board5x5::is_winner()
{
    if(this->n_moves != 24)
        return false;

    //checking diagonal wins
    for (int i:{0,1,2})
    {
        for(int j:{0,1,2})
        {

            if(board[i][j] == board[i+1][j+1] && board[i][j] == board[i+2][j+2])
            {
                if(board[i][j] == 'X')
                    x_wins++;
                else
                    o_wins++;
            }
        }
        //checks opposite diagonal wins
        for(int j:{2,3,4})
        {
            if(board[i][j] == board[i+1][j-1] && board[i][j] == board[i+2][j-2])
            {
                if(board[i][j] == 'X')
                    x_wins++;
                else
                    o_wins++;
            }
        }
    }

    //checking horizontal and vertical wins
    for(int i:{0,1,2,3,4})
    {
         for(int j:{0,1,2})
         {
               //horizontal wins
               if(board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2])
                {
                    if(board[i][j] == 'X')
                        x_wins++;
                    else
                        o_wins++;
                }
                //vertical wins
                if(board[j][i] == board[j+1][i] && board[j][i] == board[j+2][i])
                {
                    if(board[j][i] == 'X')
                        x_wins++;
                    else
                        o_wins++;
                }
         }
    }

    if(x_wins != o_wins)
    {
        show_winner();
        return true;
    }
    return false;

}

bool Board5x5::is_draw()
{
    if(this->n_moves == 24 && this->x_wins == this->o_wins)
    {
        return true;
    }
    return false;
}

bool Board5x5::game_is_over()
{
    return n_moves >= 24;
}

void Board5x5::show_winner()
{
    if(x_wins > o_wins)
    {
        cout << "Player X wins\n";
    }
    else
    {
        cout << "Player O wins\n";
    }
}





