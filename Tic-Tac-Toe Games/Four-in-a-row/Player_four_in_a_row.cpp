// Class definition for XO_Player class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1
#include<iostream>
#include<random>
#include<iomanip>
#include<algorithm>
#include"BoardGame_Classes_four_in_a_row.h"
using namespace std;

Connect4_Player::Connect4_Player(char symbol1, int order,char symbol): Player(symbol1){
    cout << "Welcome player " << order << endl;
    cout << "Please enter your name: ";
    cin >> name;
    this->symbol = symbol;
}

void Connect4_Player::get_move(int &x, int &y) {
    //to make the user choose the lowest places
    cout << "\nPlease enter your move x (0 to 5) and y (0 to 6) separated by spaces(It has to be the lowest possible option): ";
    cin >> x >> y;
}