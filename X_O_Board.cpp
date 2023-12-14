// Class definition for X_O_Board class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1
#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include "BoardGame_Classes.h"
#include "Player.cpp"
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

Connect4_Board::Connect4_Board() {
    n_rows = 6 ,n_cols = 7;
    board = new char*[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board [i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;//initialization for the 6*7 board.
    }
}

bool Connect4_Board::update_board(int x, int y, char symbol) {
    //if the user will put the symbol in the first row then just check that it's empty and exist in the board
    if(x==5 and y>-1 and y<7 and board[x][y] == 0){
        board[x][y] = toupper(symbol);//Update the board with the uppercase of the symbol
        n_moves++;
        return true;
    }
    //if it's not in the first row check also that there is a symbol under it
    if (!(x < 0 || x > 5 || y < 0 || y > 6) && (board[x][y] == 0) && (board[x+1][y]=='X' or board[x+1][y]=='O')) {
        board[x][y] = toupper(symbol);
        n_moves++;
        return true;
    }
    else
        return false;
}

void Connect4_Board::display_board() {
    //print the 6*7 board
    for (int i: {0,1,2,3,4,5}) {
        cout << "\n| ";
        for (int j: {0,1,2,3,4,5,6}) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << board [i][j] << " | ";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

bool Connect4_Board::is_winner(){
    int row=6,col=7;
    for(int i=0;i<row;i++){//Horizontal win 4 X's or 4 O's behind eachother
        int count1 =0, count2=0;
        for(int j=0;j<col;j++){
            if(board[i][j]== 'X'){
                count1++;
            }
            else count1 =0;//if there is gab then count again from the start
            if(count1==4)return true;
            if(board[i][j]== 'O'){
                count2++;
            }
            else count2 =0;
            if(count2==4)return true;
        }
    }
    for(int i=0;i<col;i++){
        //Vertical win 4 X's or 4 O's vertically
        int count1 =0,count2=0;
        for(int j=0;j<row;j++){
            if(board[j][i]== 'X'){
                count1++;
            }
            else count1 =0;
            if(count1==4)return true;
            if(board[j][i]== 'O'){
                count2++;
            }
            else count2 =0;
            if(count2==4)return true;
        }
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            int count1 =0;
            // right downward diagonal check for X's
            for(int k=0; i+k<row && j+k<col; k++){
                if(board[i+k][j+k] == 'X'){
                    count1++;
                }
                else{
                    break;
                }
                if(count1==4){
                    return true;
                }
            }
            count1 =0;
            for(int k=0; i-k>=0 && j+k<col; k++){
                // left upward diagonal check for X's
                if(board[i-k][j+k] == 'X'){
                    count1++;
                }
                else{
                    break;
                }
                if(count1==4){
                    return true;
                }
            }
        }
    }
    for(int i=0;i<row;i++){//Same for O's
        for(int j=0;j<col;j++){
            int count1 =0;
            for(int k=0; i+k<row && j+k<col; k++){
                if(board[i+k][j+k] == 'O'){
                    count1++;
                }
                else{
                    break;
                }
                if(count1==4){
                    return true;
                }
            }
            count1=0;
            for(int k=0; i-k>=0 && j+k<col; k++){
                if(board[i-k][j+k] == 'O'){
                    count1++;
                }
                else{
                    break;
                }
                if(count1==4){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Connect4_Board::is_draw() {
    //if all the cells contains symbols and there is no winner
    return(n_moves == 42 && !is_winner());
}

bool Connect4_Board::game_is_over() {
    return n_moves >= 42;
}