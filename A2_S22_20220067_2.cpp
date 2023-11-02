// File: A2_S22_20220067_2.cpp
// Purpose: A program that converts male speech to inclusive speech that includes both male and female.
// Author: Alshimaa Mohamed Abdo.
// Section: S22.
// ID: 20220067.
// TA: Rana Abdelkader.
// Date: 2 November 2023.
#include<bits/stdc++.h>
using namespace std;
int main() {
    string sent;
    getline(cin,sent);
    //To get the whole sentence.
    vector<string>words;
    for(int i=0;i<sent.size();i++){
        string word;
        while(sent[i]!=' ' && i<sent.size()){
            word+=sent[i];
            i++;
        }
        //Separate every word and put it in the vector.
        words.push_back(word);
    }
    for(int i=0 ;i<words.size();i++){
        //Converting all the possible masculine words.
        if (words[i]=="he")words[i]="he or she";
        else if(words[i]=="he?")words[i]="he or she?";
        else if(words[i]=="He")words[i]="He or she";
        else if (words[i]=="him")words[i]="him or her";
        else if (words[i]=="him.")words[i]="him or her.";
        else if (words[i]=="him?")words[i]="him or her?";
        else if (words[i]=="him,")words[i]="him or her,";
        else if (words[i]=="him!")words[i]="him or her!";
        else if (words[i]=="his")words[i]="his or her";
        else if (words[i]=="His")words[i]="His or her";
        else if (words[i]=="himself")words[i]="himself or herself";
        else if (words[i]=="himself.")words[i]="himself or herself.";
        else if (words[i]=="himself!")words[i]="himself or herself!";
        else if (words[i]=="himself?")words[i]="himself or herself?";
        else if (words[i]=="himself,")words[i]="himself or herself,";
    }
    //Print the vector.
    for(int i=0 ;i<words.size();i++){
        if(i == (words.size()-1)){
            cout<<words[i];
        }
        else
            cout<<words[i]<<' ';
    }
}