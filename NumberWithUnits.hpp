#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <map>

using namespace std;
namespace ariel
{

    class NumberWithUnits
    {
    private:
        static unordered_map<string, map<string, double>> converting_units;
        long number;
        string unit;

    public:
        NumberWithUnits(double n, string u) : number(n), unit(u)
        {
            if (converting_units.empty())
            {
                throw invalid_argument("Units must be initialized");
            }
            unordered_map<string, map<string, double>>::iterator it;
            it = converting_units.find(unit);

            if (it == converting_units.end())
            {
                throw invalid_argument("Unit must be initialize");
            }
        };

        static void read_units(ifstream &read);
        static double Conversion_function(string, string);

        double getNumber() const
        {
            return number;
        }

        string getUint() const
        {
            return unit;
        }

        //////////////////////////+//////////////////////////////////

        NumberWithUnits &operator+=(const NumberWithUnits &other)
        {
            double down = NumberWithUnits::Conversion_function(this->unit, other.unit);
            if (down != 0)
            {
                number += (other.number * down);
            }
            else
            {

                throw invalid_argument("Units do not match - [" + other.unit + "] cannot be converted to [" + this->unit + "]");
            }

            return *this;
        }
        NumberWithUnits operator+() const

        {
            return NumberWithUnits(number, unit);
        }

        friend NumberWithUnits operator+(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units);

        //////////////////////////-//////////////////////////////
        NumberWithUnits &operator-=(const NumberWithUnits &other)
        {
            double down = NumberWithUnits::Conversion_function(this->unit, other.unit);
            if (down != 0)
            {
                number -= (other.number * down);
            }
            else
            {

                throw invalid_argument("Units do not match - [" + other.unit + "] cannot be converted to [" + this->unit + "]");
            }

            return *this;
        }
        NumberWithUnits operator-() const
        {
            return NumberWithUnits(-number, unit);
        }
        friend NumberWithUnits operator-(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units);

        ////////////////////////////Logical//////////////////////////////////////////
        friend bool operator==(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units);
        friend bool operator!=(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units);
        friend bool operator<=(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units);
        friend bool operator>=(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units);
        friend bool operator<(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units);
        friend bool operator>(const NumberWithUnits &first_NumberW_Units, const NumberWithUnits &second_NumberW_Units);

        ///////////////////++ or --///////////////////////////////////
        NumberWithUnits &operator++()
        {
            number++;
            return *this;
        }

        // postfix increment:
        NumberWithUnits operator++(int dummy_flag_for_postfix_increment)
        {
            NumberWithUnits copy = *this;
            number++;
            return copy;
        }
        NumberWithUnits &operator--()
        {
            number--;
            return *this;
        }

        // postfix increment:
        NumberWithUnits operator--(int dummy_flag_for_postfix_increment)
        {
            NumberWithUnits copy = *this;
            number--;
            return copy;
        }

        ////////////////////////////////////////*/////////////////////////
        friend NumberWithUnits operator*(const NumberWithUnits &first_NumberW_Units, const double &num);
        friend NumberWithUnits operator*(const double &num, const NumberWithUnits &first_NumberW_Units);

        //////////////////////////////////////////
        friend ostream &operator<<(ostream &out, const NumberWithUnits &NumberW_Units);
        friend istream &operator>>(istream &input, NumberWithUnits &NumberW_Units);
    };

} // namespace ariel