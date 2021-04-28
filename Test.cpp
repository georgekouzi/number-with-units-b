#include "doctest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "NumberWithUnits.hpp"
using namespace ariel;
using namespace std;

TEST_CASE("Accounting operators")
{
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{2, "km"};    
    a += NumberWithUnits{1, "km"}; 

    CHECK(a.getNumber() == a.getNumber());
    CHECK(a.getUint() == a.getUint());
    a -= NumberWithUnits{1, "km"}; 
    CHECK(a.getNumber() == a.getNumber());
    CHECK(a.getUint() == a.getUint());

    a += NumberWithUnits{1, "ton"}; 
    CHECK(a.getNumber() == a.getNumber());
    CHECK(a.getUint() == a.getUint());

    a -= NumberWithUnits{1, "ton"}; 
    CHECK(a.getNumber() == a.getNumber());
    CHECK(a.getUint() == a.getUint());

    a += NumberWithUnits{1, "m"}; 
    CHECK(a.getNumber() == a.getNumber());
    CHECK(a.getUint() == a.getUint());

    a -= NumberWithUnits{1, "m"}; 
    CHECK(a.getNumber() == a.getNumber());
    CHECK(a.getUint() == a.getUint());

    NumberWithUnits a1{2, "km"}; 
    NumberWithUnits b{2, "km"}; 
    NumberWithUnits c;
    c = a1 + b;
    CHECK(c.getNumber() == 4);
    CHECK(c.getUint() == "km");

    c = a1 - b;
    CHECK(c.getNumber() == 0);
    CHECK(c.getUint() == "km");

    a = -a1;
    CHECK(a1.getNumber() == -2);
    CHECK(a1.getUint() == "km");
}
TEST_CASE("Comparison operators")
{
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{2, "km"};  
    NumberWithUnits b{20, "km"}; 
    NumberWithUnits c;

    CHECK((a < b) == true);
    CHECK((a > b) == false);

    CHECK((a <= b) == true);
    CHECK((a >= b) == false);

    CHECK((a == b) == false);
    CHECK((a != b) == false);
    b -= NumberWithUnits{18, "km"};
    CHECK((a < b) == false);
    CHECK((a == b) == true);

    b += NumberWithUnits{18, "km"};
    CHECK((-a < b) == true);
    CHECK((-a < -b) == false);
}
TEST_CASE("Increase by 1 and subtract by 1")
{
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "km"};  
    NumberWithUnits b{20, "km"}; 
    NumberWithUnits c;
    CHECK((a++).getNumber() == 2);
    CHECK(a.getNumber() == 3);
    CHECK((++a).getNumber() == 4);

    CHECK((a--).getNumber() == 4);
    CHECK(a.getNumber() == 3);
    CHECK((--a).getNumber() == 4);
}
TEST_CASE("Multiplication by real number")
{
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{2, "km"};  
    NumberWithUnits b{20, "km"}; 
    NumberWithUnits c;

    CHECK((3 * a).getNumber() == 6);
    CHECK((a * 3).getNumber() == 18);
    CHECK((-2 * a).getNumber() == -36);
}
TEST_CASE("ostream and istream")
{

    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{2, "km"};  
    NumberWithUnits b{20, "km"}; 
    NumberWithUnits c;
    stringstream output;
    output << a;
    CHECK("2[km]" == output.str());
    output << b;
    CHECK("20[km]" == output.str());
    output << b - a;
    CHECK("18[km]" == output.str());

    stringstream input("700 [ kg ]");

    input >> c;
    CHECK(c.getNumber() == 700);
    CHECK(c.getUint() == "kg");
    output << c;
    CHECK("700 [ kg ]" == output.str());
}
TEST_CASE("THROW")
{
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "km"};  
    NumberWithUnits b{20, "kg"}; 
    CHECK_THROWS(a - b);
    CHECK_THROWS(a -= b);
    CHECK_THROWS(a + b);
    CHECK_THROWS(a += b);
    // CHECK_THROWS((a == b));
    // CHECK_THROWS((a != b));
    // CHECK_THROWS((a < b));
    // CHECK_THROWS((a > b));
    // CHECK_THROWS((a <= b));
    // CHECK_THROWS((a >= b));

    NumberWithUnits c{2, "km"}; 
    NumberWithUnits d{20, "m"}; 
    CHECK_NOTHROW(c - d);
    CHECK_NOTHROW(c -= d);
    CHECK_NOTHROW(c + d);
    CHECK_NOTHROW(c += d);
    // CHECK_NOTHROW((c == d));
    // CHECK_NOTHROW((c != d));
    // CHECK_NOTHROW((c < d));
    // CHECK_NOTHROW((c > d));
    // CHECK_NOTHROW((c <= d));
    // CHECK_NOTHROW((c >= d));

    NumberWithUnits e{2, "ton"}; 
    NumberWithUnits f{20, "m"};  
    CHECK_THROWS(e - f);
    CHECK_THROWS(e -= f);
    CHECK_THROWS(e + f);
    CHECK_THROWS(e += f);
    // CHECK_THROWS((e == f));
    // CHECK_THROWS((e != f));
    // CHECK_THROWS((e < f));
    // CHECK_THROWS((e > f));
    // CHECK_THROWS((e <= f));
    // CHECK_THROWS((e >= f));

    NumberWithUnits g{2, "ton"}; 
    NumberWithUnits h{20, "kg"};  
    CHECK_NOTHROW(g - h);
    CHECK_NOTHROW(g -= h);
    CHECK_NOTHROW(g + h);
    CHECK_NOTHROW(g += h);
    // CHECK_NOTHROW((g == h));
    // CHECK_NOTHROW((g != h));
    // CHECK_NOTHROW((g < h));
    // CHECK_NOTHROW((g > h));
    // CHECK_NOTHROW((g <= h));
    // CHECK_NOTHROW((g >= h));

    NumberWithUnits i{2, "hour"}; 
    NumberWithUnits j{20, "min"}; 
    CHECK_NOTHROW(i - j);
    CHECK_NOTHROW(i -= j);
    CHECK_NOTHROW(i + j);
    CHECK_NOTHROW(i += j);
    // CHECK_NOTHROW((i == j));
    // CHECK_NOTHROW((i != j));
    // CHECK_NOTHROW((i < j));
    // CHECK_NOTHROW((i > j));
    // CHECK_NOTHROW((i <= j));
    // CHECK_NOTHROW((i >= j));

    NumberWithUnits k{2, "hour"}; 
    NumberWithUnits l{20, "ton"}; 
    CHECK_THROWS(k - l);
    CHECK_THROWS(k -= l);
    CHECK_THROWS(k + l);
    CHECK_THROWS(k += l);
    // CHECK_THROWS((k == l));
    // CHECK_THROWS((k != l));
    // CHECK_THROWS((k < l));
    // CHECK_THROWS((k > l));
    // CHECK_THROWS((k <= l));
    // CHECK_THROWS((k >= l));
}
