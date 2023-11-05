// FCAI – OOP Programming – 2023 - Assignment 2
// Program Name:				BigReal class
// Last Modification Date:	    5/11/2023
// Author1 name and ID:	        Abdelrahman Ahmed Lotfy     20220474    Obidah05@gmail.com 
// Author2 name and ID:	        Ahmed Hossam ElAlfy         20220016    ahalfy2005@gmail.com
// Author3 name and ID:	        Alshimaa Mohamed Abdo       20220067    mshmsh1582004@gmail.com
// Section:                     S22
// Teaching Assistant:          Eng/ Rana AbdelKader
// Purpose:                     A cpp class for real numbers of unlimited size, that can perform some basic operations on them. It's a solution to the problem of the limited capacities that the built-in data types like long long and double present.


#include <iostream>
#include "bigreal.h"
#include "bigreal.cpp"

using namespace std;

int main () {

    //12 testcases
    string test_cases[12] = {
        "-00009638960.0275000",
        "2333333333339.1134322222222292",
        "11.9000000000000000000000000000000001",
        "-0000000000.0000",
        "-7897506.000032873",
        "",
        "-0000054651",
        ".000654600987654000",
        "-.000000782459654",
        "847056013.23002408.000000",
        "-000000564680045610231089650000",
        "0000.0008760111548500440000000"
    };
    for (string s : test_cases)
    {
        BigReal obj1 (s), obj2("-000194.647"), obj3("+99957.062000");
        cout << obj1 << ' ' << obj1.size() << ' ' << obj1.getSign() << endl;

        BigReal obj4 (obj1 + obj2), obj5 = obj1 + obj3;
        cout << obj4 << ' ' << obj5 << endl;

        obj4 = obj2 - obj1;
        obj5 = obj3 - obj1;
        cout << obj4 << ' ' << obj4.size() << ' ' << obj4.getSign() << endl;
        cout << obj5 << ' ' << obj5.size() << ' ' << obj5.getSign() << endl;

        obj1 = obj1 + obj1 + obj4 - obj5;
        BigReal obj6 ("+04060.01500");
        if (obj1 > obj6)
        {
            cout << "obj1 is greater than obj6";
        } else if (obj1 < obj6) {
            cout << "obj1 is less than obj6";
        } else if (obj1 == obj6) {
            cout << "obj1 is equal to obj6";
        } else {
            cout << "the control shouldn't reach this statement!!";
        }
        cout << endl << endl;
    }



    //The Application
    cout<<"Welcome to BigReal application\n";
    bool isOver=true;
    while (isOver){
        cout <<"Choose the number of operation you want to apply to the two numbers:\n"
            "1-Addition\n"
            "2-Subtraction\n"
            "3-Comparison\n"
            "4-Exit\n";
        int a;
        cin>>a;
        if(a==4){
            cout<<"The program is over.";
            break;
        }
        string s1, s2;
        cout<<"Please enter the first number: ";
        cin>>s1;
        cout<<"Please enter the second number: ";
        cin>>s2;
        BigReal n1(s1),n2(s2),n3;
        if(a==1){
            n3 = n1+ n2;
            cout<<"The summation equal: "<<n3<<"\n";
        }
        else if(a==2){
            n3 = n1- n2;
            cout<<"The subtraction equal: "<<n3<<"\n";
        }
        else if(a==3){
            if(n1> n2){
                cout<<n1 <<" is the bigger number.\n";
            }
            else if(n1< n2){
                cout<<n2 <<" is the bigger number.\n";
            }
            else if(n1== n2)cout<<"Two equal numbers.\n";
        }
        else{
            cout<<"Sorry, this is not an option.";
        }
    }
    return 0;
}