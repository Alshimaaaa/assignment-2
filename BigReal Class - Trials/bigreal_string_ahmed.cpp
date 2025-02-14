#include "bigreal_string.h"

using namespace std;






//a number is valid if it contains: zero or one sign character '+'/'-' at the beginning only && zero or one '.' && any number of digits && no characters other than the mentioned 
bool BigReal::isValid(string potentialNum) {
    if (potentialNum.empty())
    {
        return false;
    }
    
    //if the first char isn't a +, -, ., nor a digit, then it's certainly in an invalid form
    bool is_dot_found = false;
    if (potentialNum[0] == '.')
    {
        is_dot_found = true;
    }
    else if (!(potentialNum[0] == '+' || potentialNum[0] == '-' || (potentialNum[0] >= '0' && potentialNum[0] <= '9')))
    {
        return false;
    }

    //start from the second char, as we have already investigated the first
    for (string::iterator itr = potentialNum.begin() + 1; itr != potentialNum.end(); itr++)
    {
        //if the current char isn't a digit
        if (!(*itr >= '0' && *itr <= '9'))
        {
            if (*itr == '.')
            {
                //if is_dot_found is true, that means that a dot has already been found before
                if (is_dot_found)
                {
                    //so finding a dot when is_dot_found is true, means that it's a second dot, which is an invalid form for a number 
                    return false;
                }
                else
                {
                    //if is_dot_found is false, and a dot is read, then that's the first dot we passed by. mark this in the flag
                    is_dot_found = true; 
                }
            }
            //if it's neither a digit nor a dot, then surely it's a foreign character that's not allowed in the valid form of a number
            else
            {
                return false;
            }
        }
    }
    return true;
}






//default constructor
BigReal::BigReal () {
    BigReal::setNum("");
}



//parametrized constructor
BigReal::BigReal (string potentialNum) {
    BigReal::setNum (potentialNum);
}






void BigReal::setNum (string potentialNum) {
    //check whether the number is valid in the first place
    if (BigReal::isValid(potentialNum))
    {
        //first we want to know whether the first char is a sign, to know where to start exactly later in the loop
        //we also want to know if a dot exists, which is identical to saying that a fractional part exists
        //we will start to check those things in the first char
        bool is_first_char_sign = false, is_dot_exist = false;
        if (potentialNum[0] == '-' || potentialNum[0] == '+')
        {
            sign = potentialNum[0];
            is_first_char_sign = true;
        }
        else
        {
            sign = '+';
            if (potentialNum[0] == '.')
            {
                is_dot_exist = true;
            }
        }

        //then, we will iterate through the integer part (if any), and extract its content and put it in integer.
        //we also won't copy the leading zeroes, so initially we will assume that there are leading zeroes
        bool in_leading_zeroes = true;
        for (string::iterator itr = potentialNum.begin() + is_first_char_sign; itr != potentialNum.end(); itr++)
        {
            //if its true, then it marks the end of the integral part
            if (*itr == '.')
            {
                is_dot_exist = true;
                break;
            }

            //as long as we are in the leading zeroes, don't copy the characters
            if (in_leading_zeroes)
            {
                //the first time we meet a non-zero character when in_leading_zeroes is true, marks the end of the leading zeroes
                if (*itr != '0')
                {
                    in_leading_zeroes = false;
                    integer.push_back(*itr);
                }
            }
            //copy the chars to integer if not in leading zeroes
            else
            {
                integer.push_back(*itr);
            }
        }

        //after searching for the dot in the previous code, if it exists only, iteratr over the fractional part
        if (is_dot_exist)
        {
            //we also won't copy the trailing zeroes, so initially we will assume that there are trailing zeroes
            bool in_trailing_zeroes = true;
            //iterate in reverse order, until the dot is reached
            for (string::reverse_iterator itr = potentialNum.rbegin(); *itr != '.'; itr++)
            {
                //as long as we are in the trailing zeroes, don't copy the characters
                if (in_trailing_zeroes)
                {
                    //the first time we meet a non-zero character when in_trailing_zeroes is true, marks the end of the trailing zeroes
                    if (*itr != '0')
                    {
                        in_trailing_zeroes = false;
                        fraction.insert(fraction.begin(), *itr);
                    }
                }
                //copy the chars to fraction if not in trailing zeroes
                else
                {
                    fraction.insert(fraction.begin(), *itr);
                }
            }
        }

        //if there were no integral part in the potential number, set integer to zero
        if (integer.empty())
        {
            integer = "0";
        }
        //likwise, if there were no fractional part in the potential number, set fraction to zero
        if (fraction.empty())
        {
            fraction = "0";
        }
    }
    //if not, then set its attributes to those default values
    else
    {
        sign = '+';
        integer = "0";
        fraction = "0";
    }
}



int BigReal::size () {
    //return the # of digits in integer + # of digits in fraction, considering that:
    //if there in no integer part, then its # of digits = 0
    //if there in no fraction part, then its # of digits = 0
    return ((integer != "0") * integer.size()) + ((fraction != "0") * fraction.size());
}



short BigReal::getSign () {
    //if the number is a zero, return 0
    if (integer == "0" && fraction == "0")
    {
        return 0;
    }
    //if it's positive, return +1.
    else if (sign == '+')
    {
        return 1;
    }
    //if it's negative, return -1.
    else
    {
        return -1;
    }
}