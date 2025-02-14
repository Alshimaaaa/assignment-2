// File: t1_p7.cpp
// Purpose: for a group of pieces of dominos, check whether they can form a chain satisfying the given condition, and if so, print it.
// Author: Ahmed Hossam Samir ElAlfy
// Section: S22
// ID: 20220016
// TA: Rana AbdelKader
// Date: 2 Nov 2023

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct domino_piece {
    int leftNu;
    int rightNu;
};


bool FormsDominoChain(vector <domino_piece> &dominos);

int main()
{
    vector <domino_piece> vec = {
        {1, 4},
        {2, 6},
        {4, 4},
        {6, 1},
        {4, 3}
    };
    /*vector <domino_piece> vec = {
        {2, 4},
        {1, 4},
        {4, 6},
        {5, 2},
        {4, 1}
    };*/
    FormsDominoChain(vec);
    return 0;
}


bool FormsDominoChain(vector <domino_piece> &dominos)
{
    //store the formed potential chain in a deque. every domino piece that is not yet part of the chain, will be in the "dominos" vector.
    static deque <domino_piece> chain;
    //there use will be known later
    static vector <domino_piece>::iterator itr_dominos;
    static deque <domino_piece>::iterator previous_insertion;
    //these booleans will work as flags that direct the work of the function, and tell it which parts to operate. 
    static bool append_to_the_right, append_to_the_left, insert_in_the_middle;
    bool have_breaked = false;

    //the occuring of this condition, marks the completness of formation of the chain, which is also the last call to this function.
    if (dominos.empty())
    {
        //but before we return true, we must check if an illusionary chain was made, that contains a piece that doesn't satisfy the condition, and return false if it was so.
        for (int i = 1, size = chain.size(); i < (size - 1); i++)
        {
            if (!((chain[i].leftNu == chain[i-1].rightNu) && chain[i].rightNu == chain[i+1].leftNu))
            {
                return false;
            }
        }

        //if we reach this point, then we have a valid chain. we will print it, then return true
        for (int i = 0, size = chain.size(); i < size; i++)
        {
            cout << chain[i].leftNu << '|' << chain[i].rightNu;
            if (i == (size - 1))
            {
                cout << '\n';
            }
            else
            {
                cout << " - ";
            }
        }
        return true;
    }
    //the occurence of this condition happens only at this first call of this function, so we will take advantage of this and initialize some variables.
    if (chain.empty())
    {
        append_to_the_right = true, append_to_the_left = false, insert_in_the_middle = false;
        //we will begin the chain with an arbitrary piece, which is the first in the dominos vector, and then erase it from the vector.
        chain.push_back(dominos[0]);
        dominos.erase(dominos.begin());
    }
    else
    {
        //first, we will try to add pieces to the right side of the chain, if the condition is satisfied.
        if (append_to_the_right)
        {
            //iterate over every piece in dominos
            for (vector <domino_piece>::iterator itr = dominos.begin(); itr != dominos.end(); itr++)
            {
                if ((chain.end()-1)->rightNu == itr->leftNu)
                {
                    //if a piece is added legally to the chain, then it must be removed from the dominos, in order to preserve the semantic meanings of every variable.
                    chain.push_back(*itr);
                    dominos.erase(itr);
                    //a signal that a piece was added to the chain.
                    have_breaked = true;
                    break;
                }
            }
            //at the first time when no piece is added to the chain via appending to the right, change the boolean flags so that they stop trying to insert pieces this way and move to trying to add them from the left.
            if (!have_breaked)
            {
                append_to_the_right = false;
                append_to_the_left = true;
            }
        }
        //second, we will try to add pieces to the left side of the chain, if the condition is satisfied.
        else if (append_to_the_left)
        {
            //iterate over every piece in dominos
            for (vector <domino_piece>::iterator itr = dominos.begin(); itr != dominos.end(); itr++)
            {
                if ((chain.begin())->leftNu == itr->rightNu)
                {
                    //if a piece is added legally to the chain, then it must be removed from the dominos, in order to preserve the semantic meanings of every variable.
                    chain.push_front(*itr);
                    dominos.erase(itr);
                    //a signal that a piece was added to the chain.
                    have_breaked = true;
                    break;
                }
            }
            //at the first time when no piece is added to the chain via appending to the left, change the boolean flags so that they stop trying to insert pieces this way and move to trying to add them to the middle of the chain.
            if (!have_breaked)
            {
                append_to_the_left = false;
                insert_in_the_middle = true;
                itr_dominos = dominos.begin();
                previous_insertion = chain.begin();
            }
        }
        //last, we will try to add pieces to the middle of the chain, if the condition is satisfied.
        else if (insert_in_the_middle)
        {
            //the occurence of this condition means that all remainig pieces in dominos couldn't be put in the chain. In such case, no chain could be formed.
            if (itr_dominos == dominos.end())
            {
                return false;
            }
            //this simply means that we first try to insert the domino piece after the last inserted piece if possible.
            if (previous_insertion->rightNu == itr_dominos->leftNu)
            {
                chain.insert(++previous_insertion, *itr_dominos);
                dominos.erase(itr_dominos);
                itr_dominos++;
            }
            //if not, then we will iterate over every piece in the chain this time, not the dominos, 
            else
            {
                for (int i = 0, size = chain.size(); i < (size - 1); i++)
                {
                    if (chain[i].rightNu == itr_dominos->leftNu)
                    {
                        //set the value of the iterator that points to the place where the new piece will be inserted.
                        previous_insertion = chain.begin() + i + 1;
                        chain.insert(previous_insertion, *itr_dominos);
                        dominos.erase(itr_dominos);
                        //reset itr_dominos to the beginning of dominos, on order to retest the remaining pieces. 
                        itr_dominos = dominos.begin();
                        have_breaked = true;
                        break;
                    }
                }
            }
            //if no piece was added, we test for the succeeding piece in dominos.
            if (!have_breaked)
            {
                itr_dominos++;
            }
        }
    }
    //we operate this function again and again on the remaining pieces in dominos, until it's empty.
    return FormsDominoChain(dominos);
}