// File: A2_S22_20220474_Q6.cpp
// Purpose: Creating 2 functions using recursion that print the binary equivalent of a number and adds a combination of suffixes to a binary number
// Author: Abdelrahman Ahmed Lotfy
// Section: S22
// ID: 20220474
// TA: ........................
// Date: 27 Oct 2023

#include <iostream>

using namespace std;

static void binaryPrint(int n)
{
    // prints n%2 from the end to the beginning of the recursive function
    if(n>1)
        binaryPrint(n/2);
    cout << n%2;
}

static void numbers(string prefix, int k)
{
    //base case
    if(k == 0)
        cout << prefix << endl;
    //recursive case that increases the prefix and decreases the size of the possibilities of k
    else
    {
        numbers(prefix + '0', k-1);
        numbers(prefix + '1', k-1);
    }
}

int main()
{
    int n;
    cin >> n;
    binaryPrint(n);
    cout << endl;

    string pre;
    int k;
    cin >> pre >> k;
    numbers(pre, k);
}
