// File: A2_S22_20220474_Q3.cpp
// Purpose: Creating a function that splits a string based on a delimiter
// Author: Abdelrahman Ahmed Lotfy
// Section: S22
// ID: 20220474
// TA: ........................
// Date: 27 Oct 2023

#include <iostream>
#include <vector>

using namespace std;

vector <string> split(string target, string delimeter)
{
    vector <string> result;
    string s = "";
    int n = target.size();
    for(int i = 0; i<n; i++)
    {
        //keeps adding characters to a string until it is equal to the delimeter in which case it will add that string to a vector and empty itself for the next word
        if(target[i] != delimeter[0])
            s += target[i];
        else
        {
            result.push_back(s);
            s = "";
        }
    }
    //for the last string if it is not empty it will be added to the vector in the event of there being no delimeter in the end
    if(s != "")
        result.push_back(s);
    return result;
}

int main()
{
   vector <string> out;
   string target, cut;
   getline(cin, target);
   getline(cin, cut);
   out = split(target, cut);
   for(int i = 0; i<out.size(); i++)
   {
       cout << out[i] << endl;
   }
}


