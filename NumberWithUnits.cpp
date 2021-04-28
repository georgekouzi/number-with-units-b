#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stack>
using namespace std;
#include "NumberWithUnits.hpp"
namespace ariel
{
    unordered_map<string, map<string,double>> NumberWithUnits::converting_units;

    double NumberWithUnits::Conversion_function(string f, string s)
    {

        map<string, double> convert;
        stack<string> st;
        st.push(f);
        convert[f] = 1;
        while (!st.empty())
        {
            string curr_key = st.top();
            st.pop();
            for (pair<string,double> curr_pair : NumberWithUnits::converting_units[curr_key])
            {
                if (convert.find(curr_pair.first) == convert.end() && NumberWithUnits::converting_units.find(curr_pair.first) != NumberWithUnits::converting_units.end())
                {
                    st.push(curr_pair.first);
                }
                convert[curr_pair.first] = curr_pair.second * convert[curr_key];
                if (curr_pair.first == s)
                {
                    return convert[curr_pair.first];
                }
            }
        }

        return 0;
    }

    

    NumberWithUnits operator+(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units)
    {
        

        double down = NumberWithUnits::Conversion_function(first_NumberW_Units.unit, second_NumberW_Units.unit);
        if (down != 0)
        {
            return NumberWithUnits(first_NumberW_Units.number + (second_NumberW_Units.number * down), first_NumberW_Units.unit);
        }
        else
        {

            throw invalid_argument("Units do not match - [" + second_NumberW_Units.unit + "] cannot be converted to [" + first_NumberW_Units.unit + "]");
        }
    }

    //////////////////////////-//////////////////////////////

    NumberWithUnits operator-(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units)
    {
        double down = NumberWithUnits::Conversion_function(first_NumberW_Units.unit, second_NumberW_Units.unit);
        if (down != 0)
        {
            return NumberWithUnits(first_NumberW_Units.number - (second_NumberW_Units.number * down), first_NumberW_Units.unit);
        }
        else
        {

            throw invalid_argument("Units do not match - [" + second_NumberW_Units.unit + "] cannot be converted to [" + first_NumberW_Units.unit + "]");
        }
    }

    ////////////////////////////Logical//////////////////////////////////////////
    bool operator==(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units)
    {

        double down = NumberWithUnits::Conversion_function(first_NumberW_Units.unit, second_NumberW_Units.unit);
        if (down != 0)
        {
            return (first_NumberW_Units.number == (second_NumberW_Units.number * down));
        }
        else
        {

            throw invalid_argument("Units do not match - [" + second_NumberW_Units.unit + "] cannot be converted to [" + first_NumberW_Units.unit + "]");
        }
    
    
    
    }
    bool operator!=(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units)
    {
        double down = NumberWithUnits::Conversion_function(first_NumberW_Units.unit, second_NumberW_Units.unit);
        if (down != 0)
        {
            return (first_NumberW_Units.number != (second_NumberW_Units.number * down));
        }
        else
        {

            throw invalid_argument("Units do not match - [" + second_NumberW_Units.unit + "] cannot be converted to [" + first_NumberW_Units.unit + "]");
        }
    }

    bool operator<=(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units)
    {

        double down = NumberWithUnits::Conversion_function(first_NumberW_Units.unit, second_NumberW_Units.unit);
        if (down != 0)
        {
            return (first_NumberW_Units.number <= (second_NumberW_Units.number * down));
        }
        else
        {

            throw invalid_argument("Units do not match - [" + second_NumberW_Units.unit + "] cannot be converted to [" + first_NumberW_Units.unit + "]");
        }
    }
    bool operator>=(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units)
    {
        double down = NumberWithUnits::Conversion_function(first_NumberW_Units.unit, second_NumberW_Units.unit);
        if (down != 0)
        {
            return (first_NumberW_Units.number >= (second_NumberW_Units.number * down));
        }
        else
        {

            throw invalid_argument("Units do not match - [" + second_NumberW_Units.unit + "] cannot be converted to [" + first_NumberW_Units.unit + "]");
        }
    }
    bool operator<(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units)
    {

        double down = NumberWithUnits::Conversion_function(first_NumberW_Units.unit, second_NumberW_Units.unit);
        if (down != 0)
        {
            return (first_NumberW_Units.number < (second_NumberW_Units.number * down));
        }
        else
        {

            throw invalid_argument("Units do not match - [" + second_NumberW_Units.unit + "] cannot be converted to [" + first_NumberW_Units.unit + "]");
        }
    }
    bool operator>(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units)
    {

        double down = NumberWithUnits::Conversion_function(second_NumberW_Units.unit, first_NumberW_Units.unit);
        if (down != 0)
        {
            return (first_NumberW_Units.number > (second_NumberW_Units.number * down));
        }
        else
        {

            throw invalid_argument("Units do not match - [" + second_NumberW_Units.unit + "] cannot be converted to [" + first_NumberW_Units.unit + "]");
        }
    }
    ////////////////////////////////////////*/////////////////////////
    NumberWithUnits operator*(const NumberWithUnits &first_NumberW_Units, const double &num)
    {
        return NumberWithUnits{first_NumberW_Units.number * num, first_NumberW_Units.unit};
    }
    NumberWithUnits operator*(const double &num, const NumberWithUnits &first_NumberW_Units)
    {
        return NumberWithUnits{first_NumberW_Units.number * num, first_NumberW_Units.unit};
    }

    //////////////////////////////////////////////////////////////////
    ostream &operator<<(ostream &out, const NumberWithUnits &NumberW_Units)
    {
        return (out << NumberW_Units.getNumber() << "[" << NumberW_Units.getUint() << "]");
    }

    static istream &getAndCheckNextCharIs(istream &input, char expectedChar)
    {
        char actualChar = ' ';
        input >> actualChar;
        if (!input)
        {
            return input;
        }
        if (actualChar != expectedChar)
        {
            // failbit is for format error
            input.setstate(ios::failbit);
        }
        return input;
    }

    istream &operator>>(istream &input, NumberWithUnits &NumberW_Units)
    {

        //---------------------------------------------
        // Does not check format
        //---------------------------------------------
        // char ch;
        // return (input >> c._re >> ch >> c._im >> ch);
        //---------------------------------------------

        //---------------------------------------------
        // Checks format, with rewind on failure.
        //---------------------------------------------
        string number;
        string unit;

        // remember place for rewinding
        ios::pos_type startPosition = input.tellg();

        if ((!(input >> number)) ||
            (!getAndCheckNextCharIs(input, '[')) ||
            (!(input >> unit)) ||
            (!(getAndCheckNextCharIs(input, ']'))))
        {

            // rewind on error
            auto errorState = input.rdstate(); // remember error state
            input.clear();                     // clear error so seekg will work
            input.seekg(startPosition);        // rewind
            input.clear(errorState);           // set back the error flag
            throw invalid_argument("Units do not match - cannot be converted ");
        }
        else
        {
            NumberW_Units.number = stod(number);
            NumberW_Units.unit = unit;
        }

        return input;
        //---------------------------------------------
    }

    ///////////////////////////////////function///////////////////////////////////
    void NumberWithUnits::read_units(ifstream &read)
    {
        string newLine;
        while (getline(read, newLine))
        {
            istringstream key_val(newLine);
            string Word;
            string key;

            pair<double, string> value;
            bool equ = false;

            while (key_val >> Word)
            {

                if (!equ && Word != "=" && Word != "1")
                {
                    key = Word;
                }
                else if (Word == "=")
                {
                    key_val >> Word;
                    value.first = stod(Word);
                    key_val >> Word;
                    value.second = Word;

                    equ = true;
                }

                // cout << key << endl;
            }
            converting_units[key][value.second] = value.first;
            unordered_map<string, pair<double, string>>::iterator it;

            // it = converting_units.find(value.second);

            // if (it == converting_units.end())
            // {
            //     converting_units[value.second] = {};
            // }

            // cout << key << " = " << converting_units[key].first << " " << converting_units[key].second << endl;
        }
    }

} // namespace ariel