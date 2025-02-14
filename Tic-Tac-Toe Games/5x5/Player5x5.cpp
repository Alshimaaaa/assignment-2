// Class definition for XO_Player class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1
#include<iostream>
#include<random>
#include<iomanip>
#include<algorithm>
#include"BoardGame_Classes5x5.hpp"
using namespace std;

Player5x5::Player5x5 (int order, char symbol):Player(symbol) {
    cout << "Welcome player " << order << endl;
    cout << "Please enter your name: ";
    cin >> name;
    this->symbol = symbol;
}

void Player5x5::get_move(int& x, int& y)
{
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}