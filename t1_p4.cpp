// File: t1_p4.cpp
// Purpose: print the prime numbers between 2 and the entered variable n inclusive, using the sieve of Eratosthenes algorithm.
// Author: Ahmed Hossam Samir ElAlfy
// Section: S22
// ID: 20220016
// TA: Rana AbdelKader
// Date: 30 Oct 2023

#include <iostream>
#include <list>

using namespace std;

bool isMultipleOf (int n, list <long long> ls);


int main()
{
    //enter n
    long long n;
    cin >> n;

    //the container that will hold the prime numbers from 2 to n inclusive
    list <long long> prime_nos;
    for (int i = 2; i <= n; i++)
    {
        //if i is not a multiple of any of the numbers already in the prime_nos container, then add the latter to the former.
        if (!isMultipleOf(i, prime_nos))
        {
            prime_nos.emplace_back(i);
            cout << i << ' ';
        }
    }

    return 0;
}

bool isMultipleOf (int n, list <long long> ls)
{
    for (long long e : ls)
    {
        if (n % e == 0)
        {
            return true;
        }
    }

    return false;
}