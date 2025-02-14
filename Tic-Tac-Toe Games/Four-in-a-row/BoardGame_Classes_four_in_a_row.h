// Class definition for XO game classes
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1
#ifndef _BoardGame_CLASSES_FOUR_IN_A_ROW_H
#define _BoardGame_CLASSES_FOUR_IN_A_ROW_H

#include "../original/BoardGame_Classes.hpp"

using namespace std;

class Connect4_Board : public Board{
public:
    Connect4_Board();
    bool update_board (int x, int y, char symbol);
    bool is_winner();
    bool is_draw();
    void display_board();
    bool game_is_over();
};

class Connect4_Player : public Player{
public:
    Connect4_Player(char symbol1, int order,char symbol);
    void get_move(int& x, int& y);
};

class Connect4_RandomPlayer : public Player{
protected:
    int dimension;
public:
    Connect4_RandomPlayer(char symbol, int dimension);
    void get_move(int& x, int& y);
};

class Connect4_GameManager : public GameManager{
public:
    Connect4_GameManager(Board* b, Connect4_Player* playerPtr[2]);
    void run();
};

#endif