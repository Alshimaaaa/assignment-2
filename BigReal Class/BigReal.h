#ifndef _BIGREAL_H
#define _BIGREAL_H


#include <iostream>
#include <deque>

using namespace std;

class BigReal {
    private:
        deque <char> integer, fraction;
        char sign;
        bool isValid (string potentialNum);

    public:
        //constructors
        BigReal ();
        BigReal (string potentialNum);
        //we will use the default copy constructor, destructor, and assignment operator overload, because there is no need to redefine them as there are no pointers (dynamic memory allocation) in the members

        //setter and characteristic givers
        void setNum (string potentialNum);
        int size ();
        int sign ();

        //arithmetic operators overloads
        BigReal operator+ (BigReal &anotherNum);
        BigReal operator- (BigReal &anotherNum);

        //relational operators overloads
        bool operator== (BigReal &anotherNum);
        bool operator< (BigReal &anotherNum);
        bool operator> (BigReal &anotherNum);

        //friend insertion operator overload 
        friend ostream& operator<< (ostream &out, BigReal num);
};


#endif