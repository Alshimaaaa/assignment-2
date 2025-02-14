// File: A2_S22_20220067_5.cpp
// Purpose: A program that manages a list of up to 10 players and their high scores.
// Author: Alshimaa Mohamed Abdo.
// Section: S22.
// ID: 20220067.
// TA: Rana Abdelkader.
// Date: 2 November 2023.
#include<bits/stdc++.h>
using namespace std;
struct player{
    string name;
    int score;
};
player playersList[10];
int n=0;
bool compare(player a, player b){
    // a function that sort the players' scores in descending order.
    if(a.score<b.score){
        return 0;
    }
    else return 1;
}
void addPlayer(){
    string pName;
    int pScore;
    cout<<"Please enter the name and the score of the player: ";
    cin>>pName>>pScore;
    if(n<10){
        //Adding the player to the list if it's not full yet.
        playersList[n].name=pName;
        playersList[n].score=pScore;
        n++;//Increment the number of players by one.
    }
    else{
        if(pScore>playersList[9].score){
            //Add it if its score is greater than the smallest score then sort.
            playersList[9].name=pName;
            playersList[9].score= pScore;
    }
    }
    sort(playersList,playersList+n,compare);
}
void print(){
    for(int i=0;i<n;i++){
        //Print the list.
        cout<<playersList[i].name<<' '<<playersList[i].score<<"\n";
    }
}
void find(){
    string pName;
    cout<<"Enter the name of the player: ";
    cin>>pName;
    for(int i=0;i<=n;i++){
        //loop till finding this player.
        if(playersList[i].name == pName){
            cout<<"This player's highest score is "<<playersList[i].score<<"\n";
            break;
        }
        if(i==n){
            cout<<"Sorry, This player isn't from the top 10.\n";
        }
    }

}
int main() {
    cout<<"Welcome to the Top 10 players program\n";
    bool done = false;
    while(!done){
        // If the user didn't exit then keep asking.
        cout<<"Please choose the function you want to apply (write the letter).\n"
              "a- add player and his score.\n"
              "b- print our top 10 players.\n"
              "c- find a player's highest score.\n"
              "d- exit the program.\n";
        char option;
        cin>>option;
        if(option == 'a'){
            addPlayer();
        }
        else if(option == 'b'){
            print();
        }
        else if(option == 'c'){
            find();
        }
        else if(option == 'd'){
            done=true;
        }
        else cout<<"Sorry this is not from the options.\n";
    }
}
