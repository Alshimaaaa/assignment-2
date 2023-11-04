// File: A2_S22_20220474_Q12.cpp
// Purpose: evaluates a text file and assigns a score on how likely it is a phishing attempt based on certain keywords.
// Author: Abdelrahman Ahmed Lotfy
// Section: S22
// ID: 20220474
// TA: ........................
// Date: 27 Oct 2023

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
//map of words and their assigned value
map <string, int> scams =
{
    {"urgent", 2},
    {"account", 3},
    {"verify", 1},
    {"update", 2},
    {"information", 3},
    {"security", 3},
    {"alert", 2},
    {"suspicious", 2},
    {"important", 2},
    {"confirmation", 1},
    {"payment", 2},
    {"login", 2},
    {"access", 2},
    {"link", 3},
    {"expired", 2},
    {"personal", 1},
    {"verify account", 2},
    {"urgent action required", 3},
    {"risk", 2},
    {"suspended", 2},
    {"reset password", 2},
    {"unusual activity", 2},
    {"limited time", 1},
    {"reward", 1},
    {"upgrade", 1},
    {"free", 3},
    {"prize", 1},
    {"details", 2},
    {"security breach", 2},
    {"update your account", 1}
};

void check_phish(string email = "phish.txt")
{
    //takes in file
    int total = 0;
    ifstream inputFile(email);
    //map to store each word and the number of times it appeared
    map <string, int> occurence;
    string word;
    //reads file word by word
    while(inputFile >> word)
    {
        //increases total for each keyword while increasing that keyword's occurence count
        if (scams.count(word)>0)
        {
            occurence[word]++;
            total += scams[word];
        }
    }
    inputFile.close();

    for(auto key : occurence)
    {
        //prints each key and how many times it appeared and the total points it scored
        string name = key.first;
        int amount = key.second;
        cout << name << ": " << amount << " occurences, " << amount * scams[name] << " points\n";

    }
    //prints the total of all the keywords
    cout << "Total points: " << total << endl;
}

int main()
{
    string s;
    cout << "enter file name: ";
    cin >> s;
    check_phish(s);
}
