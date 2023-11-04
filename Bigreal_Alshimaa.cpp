#include<bits/stdc++.h>
using namespace std;
class BigReal {
private:
    string integer, fraction;
    char sign;

public:

    BigReal () {
        sign='+';
        integer="0";
        fraction="0";
    }
    BigReal(string potentialNum);
    bool isValid(string potentialNum);
    void setNum (string potentialNum);
//    BigReal(string number);
    //relational operators overloads
    bool operator== (BigReal anotherNum);
    bool operator> (BigReal anotherNum);
    bool operator< (BigReal anotherNum);
    //friend insertion operator overload
    friend ostream& operator<< (ostream &out, BigReal number);
};

BigReal::BigReal (string potentialNum) {
    BigReal::setNum (potentialNum);
}

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


ostream& operator << (ostream& out, BigReal number) {
    // Arrange the number content and print it.
    out << number.sign << number.integer << '.' << number.fraction << '\n';
    return out;
}

bool BigReal::operator== (BigReal anotherNum) {
    //It will return true if the three conditions happen.
    // The conditions are: same sign, same integer part, same fraction part.
    return (this->sign == anotherNum.sign && this->integer == anotherNum.integer &&
    this->fraction == anotherNum.fraction);
}

bool BigReal::operator> (BigReal anotherNum){
    if(this->sign == '+' && anotherNum.sign == '-'){
        return true;// If the first BigNum's sign is +ve while the second's is -ve
        // then it will return true which mean that the first is greater.
    }
    else if(this->sign == '-' && anotherNum.sign == '+'){
        return false;// The second is the +ve one then it's greater.
    }
    else if(this->sign == '+' && anotherNum.sign == '+'){
        int intSize1 = this->integer.size() , intSize2 = anotherNum.integer.size();
        int frSize1 = this->fraction.size() , frSize2 = anotherNum.fraction.size();
        if(intSize1 > intSize2){
            // If the number of digits in the first is more than the second then it's bigger.
            return true;
        }
        else if(intSize1 < intSize2){
            // The second has more numbers.
            return false;
        }
        else{
            // The first and the second have same number of digits.
           for(int i=0 ; i<intSize1 ; i++){
               if(this->integer[i]-'0' > anotherNum.integer[i]-'0'){
                   // If there is one digit greater than the second number's digit
                   // then it's the greater number.
                   return true;
               }
               else if(this->integer[i]-'0' < anotherNum.integer[i]-'0'){
                   return false;
               }
           }
        }
        // The two numbers have the same integer value.
        // Start comparing the fraction part.
        int mn= min(frSize1, frSize2);
        for(int i=0 ; i<mn ; i++){
            // Compare the common part and the one with greater digit is the bigger.
            if(this->fraction[i]-'0' > anotherNum.fraction[i]-'0'){
                return true;
            }
            else if(this->fraction[i]-'0' < anotherNum.fraction[i]-'0'){
                return false;
            }
        }
        // If the common part is identical then the one with extra digits is greater.
        if(frSize1>frSize2){
            return true;
        }
        else if(frSize1 < frSize2){
            return false;
        }
    }
    else if(this->sign == '-' && anotherNum.sign == '-'){
        // If the signs are both negative we copy the numbers in another two big reals with positive signs.
        BigReal num1, num2;
        num1= *this, num2=anotherNum;
        num1.sign='+',num2.sign='+';
        // And compare between them using the smaller than operator 
        // like multiplying all the equation by -1 so the operator is inversed.
        return (num1< num2);
    }
    return false;// Equal numbers.
}

bool BigReal::operator< (BigReal anotherNum){
    if(this->sign == '+' && anotherNum.sign == '-'){
        // If it's a positive number and the other num is negative then it's not smaller then false.
        return false;
    }
    else if(this->sign == '-' && anotherNum.sign == '+'){
        // Our number is the only negative one then it's the small one.
        return true;
    }
    else if(this->sign == '+' && anotherNum.sign == '+'){
        int intSize1 = this->integer.size() , intSize2 = anotherNum.integer.size();
        int frSize1 = this->fraction.size() , frSize2 = anotherNum.fraction.size();
        if(intSize1 > intSize2){
            return false;
        }
        else if(intSize1 < intSize2){
            return true;
        }
        else{
           for(int i=0 ; i<intSize1 ; i++){
               // If there is one digit smaller than the second number's digit
               // then it's the smaller number.
               if(this->integer[i]-'0' > anotherNum.integer[i]-'0'){
                   return false;
               }
               else if(this->integer[i]-'0' < anotherNum.integer[i]-'0'){
                   return true;
               }
           }
        }
        // The two numbers have the same integer value.
        // Start comparing the fraction part.
        int mn= min(frSize1, frSize2);
        for(int i=0 ; i<mn ; i++){
            // Compare the common part and the one with smaller digit is the small one.
            if(this->fraction[i]-'0' > anotherNum.fraction[i]-'0'){
                return false;
            }
            else if(this->fraction[i]-'0' < anotherNum.fraction[i]-'0'){
                return true;
            }
        }
        // If the common part is identical then the one with less digits is smaller.
        if(frSize1>frSize2){
            return false;
        }
        else if(frSize1 < frSize2){
            return true;
        }
    }
    else if(this->sign == '-' && anotherNum.sign == '-'){
        // If the signs are both negative we copy the numbers in another two big reals with positive signs.
        BigReal num1, num2;
        num1= *this, num2=anotherNum;
        num1.sign='+',num2.sign='+';
        // And compare between them using the bigger than operator. 
        // Like multiplying all the equation by -1 so the operator is inversed.
        return (num1> num2);
    }

    return false;// Equal numbers.
}

int main() {
    string s1, s2;
    cin>>s1>>s2;
    if(BigReal(s1)> BigReal(s2)){
        cout<<"1st bigger\n";
    }
    else if(BigReal(s1)< BigReal(s2)){
        cout<<"2nd bigger\n";
    }
    else if(BigReal(s1)== BigReal(s2))cout<<"equal\n";
    cout<< BigReal(s1);
}

