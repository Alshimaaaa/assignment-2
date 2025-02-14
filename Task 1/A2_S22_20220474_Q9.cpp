// File: A2_S22_20220474_Q9.cpp
// Purpose: creating an implementation of the bear game using recursion
// Author: Abdelrahman Ahmed Lotfy
// Section: S22
// ID: 20220474
// TA: ........................
// Date: 27 Oct 2023

#include <iostream>

using namespace std;

static bool bears(int n)
{
    if(n < 42)
    {
        return false;
    }
    //base case
    if(n == 42)
    {
        return true;
    }
    //recursive case: for every rule goes in the function and checks if there is a path that wins the game if there is none checks another path
    if (n % 2 == 0)
        {
            if(bears(n/2))
                return true;
        }
    if(n % 3 == 0 || n % 4 == 0)
    {
        //calculation of product of last two digits
        int last = n%10;
        int before_last = (n%100) / 10;
        int result = last * before_last;

        //condition to avoid the function constantly trying to do bears(n-0)
        if(result != 0)
        {
            if(bears(n - result))
            return true;
        }
    }
    if(n % 5 == 0)
    {
        if(bears(n-42))
            return true;
    }
    //if no path wins the game then you lose
    return false;


}

int main()
{
    int n;
    cin >> n;
    bool isWon = bears(n);
    if(isWon)
        cout << "you won\n";
    else
        cout << "you lost\n";
}
