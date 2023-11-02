// File: A2_S22_20220067_8.cpp
// Purpose: A program that generates pattern of asterisks and blanks.
// Author: Alshimaa Mohamed Abdo.
// Section: S22.
// ID: 20220067.
// TA: Rana Abdelkader.
// Date: 2 November 2023.
#include<bits/stdc++.h>
using namespace std;
static void asteriskPattern(int n , int i){
    if(n==0){return;}
    asteriskPattern(n/2,i);
    for (int j=0;j<i;j++){
        cout<<"  ";
    }
    for(int j=0;j<n;j++)
    {
        cout<<"* ";
    }
    cout<<"\n";
    asteriskPattern(n/2,i+n/2);
}

int main(){
    asteriskPattern(8,0);
}