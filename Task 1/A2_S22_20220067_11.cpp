// File: A2_S22_20220067_11.cpp
// Purpose: A program that asks the user for the names of two files to
// compare between them using character by character or word by word comparison.
// Author: Alshimaa Mohamed Abdo.
// Section: S22.
// ID: 20220067.
// TA: Rana Abdelkader.
// Date: 2 November 2023.
#include<bits/stdc++.h>
using namespace std;

void charComp (vector<string>v1,vector<string>v2){
    int line = min(v1.size(),v2.size());//Take the minimum of the files' number of lines.
    bool areSame = true;
    for(int i=0 ; i<line ; i++){
        int word = min(v1[i].size(),v2[i].size());//Take the minimum of the lines' number of words.
        for(int j=0 ; j<word ; j++){
            //loop in each letter in each word in both files.
            if(v1[i][j] != v2[i][j]){
                //If the letters are not identical.
                cout<<"Different at the line number: "<<i+1<<"\n";
                cout<<"Different at the character number: "<<j+1<<"\n";
                cout<<"First file character: "<<v1[i][j]<<"\n";
                cout<<"Second file character: "<<v2[i][j]<<"\n";
                areSame= false;
                break;
            }
            if(!areSame)break;
        }
    }
    if(areSame){
        cout<<"Identical files.";
    }
}

void stringComp(vector<string>v1,vector<string>v2){
    int line = min(v1.size(),v2.size());//Take the minimum of the files' number of lines.
    bool areSame = true;
    for(int i=0 ; i<line ; i++){
        vector<string>words1,words2;
        string w;
        stringstream ss1(v1[i]);//The first line in the vector.
        while(ss1>>w){
            words1.push_back(w);//Put its words separated in the new vector.
        }
        stringstream ss2(v2[i]);//Same as the first vector.
        while(ss2>>w){
            words2.push_back(w);
        }
        int word = min(words1.size(),words2.size());//Take the minimum of the lines' number of words.
        for(int j=0 ; j<word ; j++){
            //loop in each word in each word in both files.
            if(words1[j] != words2[j]){
                //If the words are not identical.
                cout<<"Different at the line number: "<<i+1<<"\n";
                cout<<"First file word: "<<words1[j]<<"\n";
                cout<<"Second file word: "<<words2[j]<<"\n";
                areSame= false;
                break;
            }
            if(!areSame)break;
        }
    }
    if(areSame){
        cout<<"Identical files.";
    }
}

int main(){

    string s1,s2;//Enter files names.
    cout <<"Enter the first file's name(without txt): ";
    cin>>s1;
    cout <<"Enter the second file's name(without txt): ";
    cin>>s2;

    //Read both files.
    s1+=".txt";
    s2+=".txt";
    ifstream file1(s1);
    ifstream file2(s2);

    //Save them in two vectors.
    vector<string> v1,v2;
    string text1,text2;
    while (getline(file1, text1))
    {
        v1.push_back(text1);
    }
    while (getline(file2, text2))
    {
        v2.push_back(text2);
    }

    //Let the user choose which function to apply.
    cout <<"How do you want to compare the files:\n"
           "a- Character by character comparison\n"
           "b- Word by word comparison\n";
    char choice;
    cin>>choice;
    if (choice == 'a')
    {
        charComp(v1,v2);
    }
    else if (choice == 'b')
    {
        stringComp(v1,v2);
    }
    else cout<<"Sorry this is not from the options.\n";
}