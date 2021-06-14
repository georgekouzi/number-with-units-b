#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stack>
using namespace std;
#include "NumberWithUnits.hpp"
namespace ariel
{
    unordered_map<string, unordered_map<string, double>> NumberWithUnits::converting_units;

    double NumberWithUnits::Conversion_function(const string &f, const string &s)
    {
        if (f == s)
        {
            return 1;
        };

        unordered_map<string, unordered_map<string, double>>::iterator it;
        unordered_map<string, double>::iterator it1;

        it = converting_units.find(s);
        if (it == converting_units.end())
        {
            throw invalid_argument("NO convertion");
        }

        it1 = converting_units[s].find(f);

        if (it1 == converting_units[s].end())
        {
            throw invalid_argument("NO convertion");
        }

        double newval = converting_units[s][f];
        // cout << "fffffffffff " << newval << endl;

        return newval;
    }

    NumberWithUnits operator+(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units)
    {

        double value = NumberWithUnits::Conversion_function(first_NumberW_Units.unit, second_NumberW_Units.unit);
        if (value != 0)
        {
            return NumberWithUnits(first_NumberW_Units.number + (second_NumberW_Units.number * value), first_NumberW_Units.unit);
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
        if (abs(first_NumberW_Units.number - (second_NumberW_Units.number * down)) < 0.0001)
        {
          
            return true;
        }
        else
        {

            return (first_NumberW_Units.number == (second_NumberW_Units.number * down));
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

        double down = NumberWithUnits::Conversion_function(first_NumberW_Units.unit, second_NumberW_Units.unit);
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
  char left='[',right=']';
        double num=0;
        string unit;
        input >> num >> left >> unit;
        if(unit.find(right)==string::npos)
        {
            input>>right;
        }
        unit = unit.substr(0, unit.find(right));
        if(NumberWithUnits::converting_units.count(unit)==0)
        {
            throw invalid_argument("unit doesn't exist in map");
        }
        NumberW_Units.number=num;
        NumberW_Units.unit=unit;
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
            string key1;
            string key2;
            double val1;
            double val2;
            // pair<double, string> value;
            // bool equ = false;
            key_val >> Word; //1
            val1 = stod(Word);
            key_val >> Word; //km
            key1 = Word;
            key_val >> Word; //=
            key_val >> Word; //1000
            val2 = stod(Word);
            key_val >> Word; // m
            key2 = Word;

            converting_units[key1][key2] = val2 / val1;
            converting_units[key2][key1] = (val1 / val2);

            for (auto &map : converting_units[key2])
            {
                if (key1 != map.first)
                {
                    // cout << key1 << " 3 " << map.first << " " << converting_units[key1][key2] << " " << map.second << endl;

                    converting_units[key1][map.first] = converting_units[key1][key2] * map.second;
                    // cout << map.first << " 4 " << key1 << " " << 1 << " " << converting_units[key1][map.first] << endl;

                    converting_units[map.first][key1] = 1 / converting_units[key1][map.first];
                }
            }
            for (auto &map : converting_units[key1])
            {
                if (key2 != map.first)
                {
                    // cout << key2 << " 5 " << map.first << " " << converting_units[key2][key1] << " " << map.second<< " " <<<< endl;
                    converting_units[key2][map.first] = converting_units[key2][key1] * map.second;
                    // cout << map.first << " 6 " << key2 << " " << 1 << " " << converting_units[key2][map.first] << endl;
                    converting_units[map.first][key2] = 1 / converting_units[key2][map.first];
                }
            }
            // cout << key1 << " " << key2 << " " << converting_units[key1][key2] << endl;
            // cout << key2 << " " << key1 << " " << converting_units[key2][key1] << endl;
        }

        // for (auto &map : converting_units)
        // {
        //     // cout << key1 << " " << key2 << " " << converting_units[key1][key2] << endl;
        //     for (auto &map1 : map.second)
        //     {
        //         cout << map.first << " " << map1.first << " " << map1.second << endl;
        //     }
        // }
    }
} // namespace ariel