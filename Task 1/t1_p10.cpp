// File: t1_p10.cpp
// Purpose: take a file the contains a message/post, check it for specific words that are listed in another specific file, if they exist in the former file, then convert them to another word specified in the latter file.
// Author: Ahmed Hossam Samir ElAlfy
// Section: S22
// ID: 20220016
// TA: Rana AbdelKader
// Date: 1 Nov 2023

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <codecvt>

using namespace std;

void modifyArabicFile();
void modifyEnglishFile();



int main()
{
    modifyArabicFile();
}








void modifyArabicFile()
{
    //take the file name that contains the conversion table
    string lookup_table_file_name;
    cout << "enter the name of the file that contains the conversion table: ";
    cin >> lookup_table_file_name;
    lookup_table_file_name += ".txt";

    //after adding the proper extension, open it in reading mode
    wifstream lookup_table_file (lookup_table_file_name);
    //a line code to enable the program to deal with arabic letters in unicode
    lookup_table_file.imbue(locale(lookup_table_file.getloc(), new std::codecvt_utf8<wchar_t>));
    //extract all the words and their replacements from the lookup_table file, and put them in the map
    unordered_map <wstring, wstring> lookup_table; 
    wstring key, value;
    while (!lookup_table_file.eof())
    {
        getline (lookup_table_file, key, L':');
        getline (lookup_table_file, value, L'\n');
        //lookup_table_file >> key >> value;
        lookup_table[key] = value;
    }
    lookup_table_file.close();

    //take the file name that contains the post/message
    string inFile_name;
    cout << "enter the name of the file that contains the post/message: ";
    cin >> inFile_name;
    inFile_name += ".txt";

    //opent the file, and create an auxilary file that will contain the modified message/post
    wfstream inFile (inFile_name);
    //a line code to enable the program to deal with arabic letters in unicode
    inFile.imbue(locale(inFile.getloc(), new std::codecvt_utf8<wchar_t>));
    string modified_fileName = "modified_" + inFile_name;
    wofstream modified (modified_fileName);
    //a line code to enable the program to deal with arabic letters in unicode
    modified.imbue(locale(modified.getloc(), new std::codecvt_utf8<wchar_t>));

    //for the whole file, do the following
    wstring word;
    wchar_t c;
    while (!inFile.eof())
    {
        //while the char encountered is an arabic alphabetical letter, add it to the word
        do
        {
            inFile.get(c);
            word.push_back(c);
        }
        while ((!inFile.eof()) && (c >= L'\u0600' && c <= L'\u06FF'));
        //while ((!inFile.eof()) && (c >= L'\u0621' && c <= L'\u063A' && c >= L'\u0641' && c <= L'\u064A'));
        //a non-alphabetical char will always be added by mistake, so remove it
        word.pop_back();

        //if this word exists in the lookup table, write its replacemen from the map in modified       
        if (lookup_table.find(word) == lookup_table.end())
        {
            modified << word << c;
        }
        //else write it as it is
        else
        {
            modified << lookup_table[word] << c;
        }

        word.clear();
    }

    //close the files
    inFile.close();
    modified.close();
}












void modifyEnglishFile()
{
    //take the file name that contains the conversion table
    string lookup_table_file_name;
    cout << "enter the name of the file that contains the conversion table: ";
    cin >> lookup_table_file_name;
    lookup_table_file_name += ".txt";

    //after adding the proper extension, open it in reading mode
    ifstream lookup_table_file (lookup_table_file_name);
    //extract all the words and their replacements from the lookup_table file, and put them in the map
    unordered_map <string, string> lookup_table; 
    string key, value;
    while (!lookup_table_file.eof())
    {
        getline (lookup_table_file, key, ':');
        getline (lookup_table_file, value, '\n');
        lookup_table[key] = value;
    }
    lookup_table_file.close();

    //take the file name that contains the post/message
    string inFile_name;
    cout << "enter the name of the file that contains the post/message: ";
    cin >> inFile_name;
    inFile_name += ".txt";

    //opent the file, and create an auxilary file that will contain the modified message/post
    fstream inFile (inFile_name);
    string modified_fileName = "modified_" + inFile_name;
    ofstream modified (modified_fileName);

    //for the whole file, do the following
    string word;
    char c;
    while (!inFile.eof())
    {
        //while the char encountered is an alphabetical letter, add it to the word
        do
        {
            inFile.get(c);
            word.push_back(c);
        }
        while ((!inFile.eof()) && ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')));
        //a non-alphabetical char will always be added by mistake, so remove it
        word.pop_back();

        //if this word exists in the lookup table, write its replacemen from the map in modified       
        if (lookup_table.find(word) == lookup_table.end())
        {
            modified << word << c;
        }
        //else write it as it is
        else
        {
            modified << lookup_table[word] << c;
        }

        word.clear();
    }

    //close the files
    inFile.close();
    modified.close();
}