// FCAI – OOP Programming – 2023 - Assignment 2
// Program Name:				BigReal class
// Last Modification Date:	    5/11/2023
// Author1 name and ID:	        Abdelrahman Ahmed Lotfy     20220474    Obidah05@gmail.com 
// Author2 name and ID:	        Ahmed Hossam ElAlfy         20220016    ahalfy2005@gmail.com
// Author3 name and ID:	        Alshimaa Mohamed Abdo       20220067    mshmsh1582004@gmail.com
// Section:                     S22
// Teaching Assistant:          Eng/ Rana AbdelKader
// Purpose:                     A cpp class for real numbers of unlimited size, that can perform some basic operations on them. It's a solution to the problem of the limited capacities that the built-in data types like long long and double present.


#include "bigreal.h"
#include <algorithm>

using namespace std;






char BigReal::reverseSign()
{
    //returns the opposite sign of the first bigreal object
    if(this->sign == '+')
        return '-';
    return '+';
}



void BigReal::zero(BigReal &anotherNum)
{
    //this functions adds leading or trailing zeros
    // the absolute values x and y determine the amount of zeros to be added
    int x = this->integer.size() - anotherNum.integer.size();
    int y = this->fraction.size() - anotherNum.fraction.size();
    if (this->integer.size() > anotherNum.integer.size())
    {
        for(int i = 0; i < abs(x); i++)
        {
            //adds zeros to the beginning of the integer
            anotherNum.integer = '0' + anotherNum.integer;
        }
    }
    else if(this->integer.size() < anotherNum.integer.size())
    {
        for(int i = 0; i < abs(x); i++)
        {
            this->integer = '0' + this->integer;
        }
    }
    if (this->fraction.size() > anotherNum.fraction.size())
    {
        for(int i = 0; i < abs(y); i++)
        {
            //adds zeros to the end of the fraction part
            anotherNum.fraction += '0';
        }
    }
    else if(this->fraction.size() < anotherNum.fraction.size())
    {
        for(int i = 0; i < abs(y); i++)
        {
            this->fraction += '0';
        }
    }
}



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






BigReal BigReal::operator+ (BigReal &anotherNum)
{
    char originalSign1 = this->sign, originalSign2 = anotherNum.sign;
    //adds leading and trailing zeros as needed
    zero(anotherNum);
    //if both signs are equal it can add normally. otherwise it would be a subtraction case.
    if(this->sign == anotherNum.sign)
    {
        //reverses integer and fraction parts in order to add the smaller values first while being able to deal with any carry easily
        int sum, digit1, digit2, icarry = 0, fcarry = 0;
        string iresult, fresult;
        string frac1 = this->fraction, frac2 = anotherNum.fraction;
        reverse(frac1.begin(), frac1.end());
        reverse(frac2.begin(), frac2.end());
        string integer1 = this->integer, integer2 = anotherNum.integer;
        reverse(integer1.begin(), integer1.end());
        reverse(integer2.begin(), integer2.end());

        for(int i = 0; i < frac1.size(); i++)
        {
            //conversion to int
            digit1 = frac1[i] - '0';
            digit2 = frac2[i] - '0';
            //adding each digit including carry
            sum = digit1 + digit2 + fcarry;
            fcarry = sum/10;
            if(i == frac1.size() - 1)
            {
                // for the last fraction number it would take the carry over to the integer part
                icarry = fcarry;
                fcarry = 0;
            }
            //converts value back to string and adds it to result
            fresult += (sum%10) + '0';

        }
        //reverses the fraction back
        reverse(fresult.begin(), fresult.end());
        int i = 0, j = 0;
        while (i < integer1.size() || j < integer2.size() || icarry > 0)
        {
            //each integer digit follows a different index in order to be able to increase the biggest number in the event of there being a carry
            digit1 = 0;
            digit2 = 0;
            if(i < integer1.size())
                digit1 = integer1[i] - '0';
            if(j < integer2.size())
                digit2 = integer2[j] - '0';

            sum = digit1 + digit2 + icarry;
            icarry = sum / 10;
            iresult += (sum % 10) + '0';
            i++;
            j++;
        }
        reverse(iresult.begin(), iresult.end());
        //combines the numbers in bigreal format
        string output = this->sign + iresult + '.' + fresult;

        return BigReal{output};
    }

    else
    {

        //changes the sign of the second number and turns it into a subtraction problem
        BigReal temp = anotherNum, result;

        if(this->sign == '+' && anotherNum.sign == '-')
            {
                //treats the calculation as if subtracting two positive numbers
                temp.sign = '+';
                anotherNum = temp;
                result = operator-(anotherNum);
                //converts the sign back to its original value in case any changes occurred
                anotherNum.sign = originalSign2;
                return result;
            }

        else
        {
            //treats the calculation as negative - negative and adjusts the sign in some cases
            temp.sign = '-';
            anotherNum = temp;
            result = operator-(anotherNum);
            if(operator<(anotherNum) && result.sign == '+')
            {
                result.sign = '-';
            }
            //converts the sign back to its original value in case any changes occurred
            anotherNum.sign = originalSign2;
            return result;
        }

    }
}



BigReal BigReal::operator- (BigReal &anotherNum)
{
    char originalSign2 = anotherNum.sign;
    zero(anotherNum);
    string fresult, iresult, frac1 = this->fraction, frac2 = anotherNum.fraction;
    string integer1 = this->integer, integer2 = anotherNum.integer;
    int diff, digit1, digit2, iborrow = 0, fborrow = 0;
    char newSign = this->sign;
    //for these sign combinations, the calculation turns into addition
    if((this->sign == '+' && anotherNum.sign == '-') || (this->sign == '-' && anotherNum.sign == '+'))
    {
        //changes the sign of the second number and treats it as addition
        if(anotherNum.sign == '-')
            anotherNum.sign = '+';
        else
            anotherNum.sign = '-';
        BigReal result = operator+(anotherNum);
        //converts the sign back to its original value in case any changes occurred
        anotherNum.sign = originalSign2;
        return result;
    }
    else
    {

            //since two consecutive negative signs are equal to a positive sign, the sign of the second number is changed
            if(this->sign == '-' && anotherNum.sign == '-')
            {
                anotherNum.sign = '+';
            }


            //in case the first number is smaller than the second number, switches the variables holding them so that the bigger number is subtracted first and switches the sign
            if(operator<(anotherNum) || this->sign == '-' && anotherNum.sign == '+')
            {
                if((this->sign == '+' && anotherNum.sign == '+'))
                {
                    frac1 = anotherNum.fraction, frac2 = this->fraction;
                    integer1 = anotherNum.integer, integer2 = this ->integer;
                    newSign = reverseSign();
                }
            }



            for (int i = frac1.size() - 1; i >=0; i--)
            {

                //converting to integer and calculating difference for each digit
                digit1 = frac1[i] - '0';
                digit2 = frac2[i] - '0';
                diff = digit1 - digit2 - fborrow;

                if(diff < 0)
                {
                    //whenever a negative value appears, borrows from the previous value
                    diff += 10;
                    fborrow = 1;
                }
                else
                {
                    fborrow = 0;
                }
                if(i == 0)
                {
                    //for the last fraction number borrows from the integer part
                    iborrow = fborrow;
                    fborrow = 0;
                }
                //converting back to string and adding to the beginning of the fraction part
                fresult = to_string(diff) + fresult;
            }

            for (int i = integer1.size() - 1; i >=0; i--)
            {
                digit1 = integer1[i] - '0';
                digit2 = integer2[i] - '0';
                diff = digit1 - digit2 - iborrow;
                if(i == 0 && digit1 < digit2 + iborrow)
                {
                    //for the most significant integer, there is nothing to borrow from so it changes the sign
                    newSign = reverseSign();
                }

                if(diff < 0)
                {
                    if(i>0)
                    {
                        //borrows for all values except the most significant one
                        diff += 10;
                        iborrow = 1;
                    }
                    else
                    {
                        diff = diff * -1;
                    }
                }
                else
                {
                    iborrow = 0;
                }
                iresult = to_string(diff) + iresult;
            }
            string output = newSign + iresult + '.' + fresult;
            //converts the sign back to its original value in case any changes occurred
            anotherNum.sign = originalSign2;
            return BigReal{output};


    }

}






bool BigReal::operator== (BigReal anotherNum) {
    //It will return true if the three conditions happen.
    // The conditions are: same sign, same integer part, same fraction part.
    return (this->sign == anotherNum.sign && this->integer == anotherNum.integer &&
    this->fraction == anotherNum.fraction);
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






ostream& operator << (ostream& out, BigReal number) {
    // Arrange the number content and print it.
    if(number.integer=="0" && number.fraction=="0"){
        // Cout the zero with no signs or fraction.
        out<<"0";
    }
    else if(number.fraction=="0" && number.sign=='+'){
        // No fraction part and sign is positive then just return the integer part.
        out<<number.integer;
    }
    else if(number.fraction=="0" && number.sign=='-'){
        // The integer part with the negative sign.
        out<<number.sign<<number.integer;
    }
    else if(number.sign=='+'){
        // Return the number without the positive sign.
        out << number.integer << '.' << number.fraction ;
    }
    else{
        // Return the full number
        out << number.sign << number.integer << '.' << number.fraction;
    }
    return out;
}