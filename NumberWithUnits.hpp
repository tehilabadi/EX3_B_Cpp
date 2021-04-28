#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
using namespace std;
namespace ariel{
    class NumberWithUnits{
        double num;
        string sizeUnit;
        public:
        double getNum()const;
        string getUnit();
        NumberWithUnits( double num,const string& sizeUnit);
        static void fillTheMap(string const& unit1, string const& unit2);
        static void read_units(std::ifstream &units_file);
        NumberWithUnits operator+(const NumberWithUnits& other)const;
        NumberWithUnits operator-(const NumberWithUnits& other)const;
        NumberWithUnits& operator-=(const NumberWithUnits& other);
        NumberWithUnits& operator+=(const NumberWithUnits& other);
        NumberWithUnits& operator++();
        NumberWithUnits& operator--();
        NumberWithUnits operator++(int);
        NumberWithUnits operator--(int);
        bool operator == (const NumberWithUnits& other)const;
        bool operator >= (const NumberWithUnits& other)const;
        bool operator <= (const NumberWithUnits& other)const;
        bool operator != (const NumberWithUnits& other)const;
        bool operator > (const NumberWithUnits& other)const;
        bool operator < (const NumberWithUnits& other)const;
        NumberWithUnits operator-()const;
        NumberWithUnits operator+()const;
        NumberWithUnits operator-();
        NumberWithUnits operator+();
        friend NumberWithUnits operator*(double other,NumberWithUnits S);
        friend NumberWithUnits operator*(int other,ariel::NumberWithUnits S);
        friend NumberWithUnits operator*(NumberWithUnits S,double other);
        friend NumberWithUnits operator*(ariel::NumberWithUnits S,int other);
        friend std::ostream& operator<< (std::ostream& output, const NumberWithUnits& c);
        friend std::istream& operator>> (std::istream& input , NumberWithUnits& c);

};
        
}