// Class definition for XO game classes
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1
#ifndef _BoardGame_CLASSES5x5_H
#define _BoardGame_CLASSES5x5_H

#include "../original/BoardGame_Classes.hpp"

using namespace std;

class Board5x5:public Board
{
private:
    //no of x wins and o wins at the end
    int x_wins, o_wins;
public:
    Board5x5();
    bool update_board (int x, int y, char symbol);
    bool is_winner();
    bool is_draw();
    void display_board();
    bool game_is_over();
    void show_winner();
};

//exactly the same as normal player but asks for a 0 to 4 range
class Player5x5:public Player
{
public:
    Player5x5 (int order, char symbol);
    void get_move(int& x, int& y);
};

#endif