// File name:   pyramic_TTT_Player.cpp
// Purpose:     implementation of the pyramic_TTT_Player class
// Author(s):   Ahmed Hossam Samir ElAlfy        
// ID(s):       20220016
// Section:     S22
// Date:        13 December 2023

#include <iostream>
#include "pyramic_TTT.hpp"

using namespace std;

//the only change from the parent class is in the overriden function get_move, where the printed message is different.

Pyramic_TTT_Player::Pyramic_TTT_Player (char symbol) : Player (symbol) {}
Pyramic_TTT_Player::Pyramic_TTT_Player (int order, char symbol) : Player (order, symbol) {}


void Pyramic_TTT_Player::get_move (int &x, int &y) {
    cout  << '\n' << "please enter a valid location coordinate as those shown in the board dispaly above, separated by spaces: ";
    cin >> x >> y;
}