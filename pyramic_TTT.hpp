// File name:   pyramic_TTT.hpp
// Purpose:     header file for the classes derived from the parent BoardGame_Classes
// Author(s):   Ahmed Hossam Samir ElAlfy        
// ID(s):       20220016
// Section:     S22
// Date:        12 December 2023

#ifndef _PYRAMIC_TTT_HPP
#define _PYRAMIC_TTT_HPP

#include "BoardGame_Classes.hpp"

class Pyramic_TTT_Board : public Board {
    private:
        //the 2 below functions detect if there's a winner.
        bool is_3_in_a_row (int rowIndex, int colIndex, string type);
        bool is_horizontal_win ();
    public:
        Pyramic_TTT_Board ();
        bool update_board (int x, int y, char symbol);
        bool is_winner();
        bool is_draw();
        void display_board();
        bool game_is_over();
};

class Pyramic_TTT_Player : public Player {
    public:
        Pyramic_TTT_Player (char symbol);
        Pyramic_TTT_Player (int order, char symbol);
        void get_move (int &x, int &y);
};

#endif