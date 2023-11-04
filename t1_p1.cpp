// File: t1_p1.cpp
// Purpose: ensure that the entered sentence is correcly spaced and letter-cased, and if not so modify it
// Author: Ahmed Hossam Samir ElAlfy
// Section: S22
// ID: 20220016
// TA: Rana AbdelKader
// Date: 30 Oct 2023

#include <iostream>
#include <cmath>

using namespace std;

void adjustCase(string::iterator itr, bool is_capitalize);
void adjustBlanks(string &s, string::iterator itr);


int main()
{
    //get the string
    string s;
    getline(cin, s, '.');

    string::iterator itr = s.begin();
    //make sure that the first letter in the sentence is capial
    adjustCase(itr, true);

    ++itr;
    //iteratie over the whole sentence and adjust the letters' cases and whitespces
    for (; itr != s.end(); itr++)
    {
        adjustCase(itr, false);
        adjustBlanks(s, itr);
    }

    //finally print the adjusted string
    cout << s << '.';
    return 0;
}


void adjustCase(string::iterator itr, bool is_capitalize)
{
    //if is_capitalize == true, this line will capitalize the letter if it's small, if it's equal to false, it will convert a letter to lower case if it's in upper case
    *itr += ((*itr >= (65 + (is_capitalize * 32))) && (*itr <= (90 + (is_capitalize * 32)))) * pow(-1, is_capitalize) * 32;
}

void adjustBlanks(string &s, string::iterator itr)
{
    bool is_single_blank_set = false;
    //detect if there are any whitespces or new lines. while they appear, do the following
    while (*itr == ' ' || *itr == '\n')
    {
        //if that's the first character to be a blank, then set the one blank of the adjusted sentence
        if (!is_single_blank_set)
        {
            *itr = ' ';
            itr++;
            is_single_blank_set = true;
        }
        //then for any other blank other than the first, erase it
        else
        {
            s.erase(itr);
        }
    }
}