// File name:   pyramic_TTT_Board.cpp
// Purpose:     implementation of the pyramic_TTT_Board class
// Author(s):   Ahmed Hossam Samir ElAlfy        
// ID(s):       20220016
// Section:     S22
// Date:        12 December 2023

#include <iostream>
#include "pyramic_TTT.hpp"

using namespace std;

Pyramic_TTT_Board::Pyramic_TTT_Board () {
    //this will create a rectangle with length 5 and width 3, which means that there will be redundant cells outside the pyramid. the implementation will take care to deal with them properly.
    n_rows = 3;
    n_cols = 5;
    int middleCol_index = 2;

    board = new char* [n_rows];
    //for every row
    for (int i : {0, 1, 2})
    {
        board[i] = new char [n_cols];
        //for every column
        for (int j : {0, 1, 2, 3, 4})
        {
            //if the cell belongs to the defined pyramic shape, initialize it with a space char, else if it's outside it and inside the created rectangle, initialize it with a hyphen char.
            if ((middleCol_index - i <= j) && (j <= middleCol_index + i))
            {
                board[i][j] = ' ';
            }
            else
            {
                board[i][j] = '-';
            }
        }
    }
}

bool Pyramic_TTT_Board::update_board (int x, int y, char symbol) {
    //check if coordinates are out of bounds, or out of the pyramid, or inside the pyramid but a symbol already lies there, respectively.
    if (x < 0 || x > 2 || y < 0 || y > 4 || board[x][y] == '-' || board[x][y] != ' ')
    {
        return false;
    }
    else
    {
        board[x][y] = symbol;
        n_moves++;
        return true;
    }
}

bool Pyramic_TTT_Board::is_winner () {

    //The current player wins if there are 3 of the same symbol in a row in the vertical column, diagonal to the left, diagonal to the right, or in one of the 4 possible horizontal adjacent cells.
    return (is_3_in_a_row(0, 2, "V") || is_3_in_a_row(0, 2, "LD") || is_3_in_a_row(0, 2, "RD") || is_horizontal_win());
}

bool Pyramic_TTT_Board::is_draw () {
    //true when no cells are left empty and there is no winner.
    return (n_moves == 9 && !is_winner());
}

void Pyramic_TTT_Board::display_board () {
    //for every row
    for (int i : {0, 1, 2}) {
        cout << '\n';
        //don't print the cells that are at the left of the row and belong to the rectangle of the board but don't belong to the pyramid. leave a blank space in their place
        //the formula ((5 - (1 + (2 * i))) / 2) calculates the # of cells not belonging to the pyramid for one side of every row.
        for (int j = 0; j < (5 - (1 + (2 * i))) / 2; j++)
        {
            cout << "          ";
        }
        //print the cells that belong to the pyramid, indexing them 0-based.
        //the formula (1 + (2 * i)) claculates the # of cells belonging to the pyramid for every row
        for (int j = ((5 - (1 + (2 * i))) / 2), n_iterations = 0; n_iterations < (1 + (2 * i)); j++, n_iterations++) {
            cout << "| (" << i << "," << j << ')';
            cout << ' ' << board [i][j] << ' ';
        }
        cout << '|';
        //don't print the cells that are at the right of the row and belong to the rectangle of the board but don't belong to the pyramid        
        for (int j = 0; j < (5 - (1 + (2 * i))) / 2; j++)
        {
            cout << "          ";
        }
        cout << "\n----------------------------------------------------";
    }
    cout << '\n';
}

bool Pyramic_TTT_Board::game_is_over () {
    return (is_winner() || is_draw());
}



bool Pyramic_TTT_Board::is_3_in_a_row (int rowIndex, int colIndex, string type) {
    //the tpes passed to the 3rd parameter may be:
    //V: vertical,
    //H: horizontal,
    //LD: left daigonal,
    //or RD: right diagonal
    //in all the types except the H, it's designed that 0, 2 are always the first 2 arguments, respectively.
    int begRowIndex = rowIndex, begColIndex = colIndex;

    //the first cell is ensured to not be empty first, then we ensure that the first == second, and the first == third, respectively.
    //logic that can be deduced by experimentation is employed to change the variables rowIndex and colIndex, accoriding to the type of adjacency we want to examine, to address the correct cells.
    return (board[begRowIndex][begColIndex] != ' ') &&
    (board[begRowIndex][begColIndex] == board[rowIndex += (type != "H")][(type == "V")? colIndex : ((type == "LD")? --colIndex : ++colIndex)]) &&
    (board[begRowIndex][begColIndex] == board[rowIndex += (type != "H")][(type == "V")? colIndex : ((type == "LD")? --colIndex : ++colIndex)]);
}

bool Pyramic_TTT_Board::is_horizontal_win () {
    //examine the 2nd (middle) row
    if (is_3_in_a_row (1, 1, "H"))
    {
        return true;
    }
    //if not, then examine the 3rd (bottom) row
    else
    {
        //examine each of the 3 possible sets of 3 adjacent cells.
        for (int j = 0; j < 3; j++)
        {
            if (is_3_in_a_row (2, j, "H"))
            {
                return true;
            }
        }
        return false;
    }
}