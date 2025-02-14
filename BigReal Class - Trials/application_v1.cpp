#include <iostream>
#include "bigreal.h"
#include "bigreal.cpp"

using namespace std;

int main () {

    //test cases
    string test_cases[12] = {};
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
    }


    //the application
    BigReal num 
    return 0;
}