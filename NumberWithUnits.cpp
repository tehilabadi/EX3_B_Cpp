#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>
using namespace std;
const double TOLERANCE = 0.001;

#include "NumberWithUnits.hpp"
namespace ariel{
    static unordered_map<string ,unordered_map< string, double>> list;
    NumberWithUnits::NumberWithUnits(double num, const string& sizeUnit){
    if(list.find(sizeUnit)==list.end()||sizeUnit.length()==0){
            throw(invalid_argument{"Units do not match1"});
    }
    this->num = num;
    this->sizeUnit = sizeUnit;
    }
    
    double NumberWithUnits::getNum()const{
        return num;
    }
    string NumberWithUnits::getUnit(){
        return sizeUnit;
    }

    void NumberWithUnits::read_units(std::ifstream &units_file){
        string unit1;
        string unit2;
        double num1=0;
        double num2=0;  
        char eq=0;      
        while (units_file>>num1>>unit1>>eq>>num2>>unit2) {
            list[unit1][unit2] = num2;
            list[unit2][unit1] = double(1/num2);
            NumberWithUnits::fillTheMap(unit1,unit2);  
        }
    }
    void NumberWithUnits::fillTheMap(string const& unit1, string const& unit2){
        for(auto& A :list[unit1]){
            list[unit2][A.first] = list[unit2][unit1]*list[unit1][A.first];
            list[A.first][unit2] = list[A.first][unit1]*list[unit1][unit2];
        }
        for(auto& A :list[unit2]){
            list[unit1][A.first] = list[unit1][unit2]*list[unit2][A.first];
            list[A.first][unit1] = list[A.first][unit2]*list[unit2][unit1];
        }
    }
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& other) const {
        if(list[this->sizeUnit].find(other.sizeUnit)==list[this->sizeUnit].end()){
            throw(invalid_argument{"Units do not match+"});
        }
        double temp = other.num*list[other.sizeUnit][this->sizeUnit];
        double ans = this->num + temp;
        return(NumberWithUnits{ans,this->sizeUnit});
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& other) const {
        if(list[this->sizeUnit].find(other.sizeUnit)==list[this->sizeUnit].end()){
            throw(out_of_range{"Units do not match-"});
        }
        double temp = other.num*list[other.sizeUnit][this->sizeUnit];
        double ans = this->num - temp;
        return(NumberWithUnits{ans,this->sizeUnit}); 
    }

    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& other){
        if(list[this->sizeUnit].find(other.sizeUnit)==list[this->sizeUnit].end()||
            list[other.sizeUnit].find(sizeUnit)==list[sizeUnit].end()){
            throw(out_of_range{"Units do not match-="});
        }
        double temp = other.num*list[other.sizeUnit][this->sizeUnit];
        this->num =this->num - temp;
        return(*this); 
    }
    
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& other){
        if(list[this->sizeUnit].find(other.sizeUnit)==list[this->sizeUnit].end()){
            throw(out_of_range{"Units do not match+="});
        }
        double temp = other.num*list[other.sizeUnit][this->sizeUnit];
        (this->num)=this->num+temp;
        return (*this);
    }

    NumberWithUnits& NumberWithUnits::operator++(){
        this->num++;
        return(*this);
    }
    NumberWithUnits NumberWithUnits::operator++(int){   
        NumberWithUnits copy = *this;
        this->num++;
        return(copy);
    }
    NumberWithUnits& NumberWithUnits::operator--(){
        this->num--;
        return(*this);
    }
    NumberWithUnits NumberWithUnits::operator--(int){
        return(NumberWithUnits{this->num--,this->sizeUnit});
    }
    bool NumberWithUnits::operator == (const NumberWithUnits& other)const{
        if(list[this->sizeUnit].find(other.sizeUnit)==list[this->sizeUnit].end()){
            throw(out_of_range{"Units do not match=="});
        }
        if(this->sizeUnit==other.sizeUnit){
            return (TOLERANCE>=abs(this->num-other.num));
        }
        return(TOLERANCE>=abs((list[other.sizeUnit][sizeUnit]*other.num)-this->num)||
        TOLERANCE>=abs((this->num-list[other.sizeUnit][sizeUnit]*other.num)));
    }
    bool NumberWithUnits::operator >= (const NumberWithUnits& other)const{
        if(list[this->sizeUnit].find(other.sizeUnit)==list[this->sizeUnit].end()){
            throw(out_of_range{"Units do not match>="});
        }
        return(this->operator==(other)||this->operator>(other));
    }
    bool NumberWithUnits::operator <= (const NumberWithUnits& other)const{
        if(list[this->sizeUnit].find(other.sizeUnit)==list[this->sizeUnit].end()){
            throw(out_of_range{"Units do not match<="});
        }
        return(this->operator==(other)||this->operator<(other));
    }
    bool NumberWithUnits::operator != (const NumberWithUnits& other)const{
        if(list[this->sizeUnit].find(other.sizeUnit)==list[this->sizeUnit].end()){
            throw(out_of_range{"Units do not match!="});
        }
        return !(this->operator==(other));
    }
    bool NumberWithUnits::operator > (const NumberWithUnits& other)const{
        if(list[this->sizeUnit].find(other.sizeUnit)==list[this->sizeUnit].end()){
            throw(out_of_range{"Units do not match>"});
        }
        return(!this->operator<=(other)); 
    }
    bool NumberWithUnits::operator < (const NumberWithUnits& other)const{
        if(list[this->sizeUnit].find(other.sizeUnit)==list[this->sizeUnit].end()){
            throw(out_of_range{"Units do not match<"});
        }
        return(num<(list[other.sizeUnit][sizeUnit]*other.num)); 
    }
    NumberWithUnits operator*(double other,ariel::NumberWithUnits S){
        return (NumberWithUnits {double(S.num*other),S.sizeUnit});
    }
    NumberWithUnits operator*(int other,ariel::NumberWithUnits S){
        return (NumberWithUnits {double(S.num*other),S.sizeUnit});
    }
    NumberWithUnits operator*(ariel::NumberWithUnits S,double other){
        return (NumberWithUnits {double(S.num*other),S.sizeUnit});
    }
    NumberWithUnits operator*(ariel::NumberWithUnits S,int other){
        return (NumberWithUnits {double(S.num*other),S.sizeUnit});
    }
    NumberWithUnits NumberWithUnits::operator-()const{
        return (NumberWithUnits{(-num),this->sizeUnit});
    }
    NumberWithUnits NumberWithUnits::operator+()const{
        return (NumberWithUnits{num,this->sizeUnit});

    }
    NumberWithUnits NumberWithUnits::operator-(){
        return (NumberWithUnits{(-num),this->sizeUnit});
    }
    NumberWithUnits NumberWithUnits::operator+(){
        return (NumberWithUnits{num,this->sizeUnit});

    }

    std::ostream& operator<< (std::ostream& output, const NumberWithUnits& c){
        return (output<<c.num<<"["<<c.sizeUnit<<"]");
    }

    static istream& getAndCheckNextChar(istream& input, char exp){
        char actual=0;
        input>>actual;
        if(!input){return input;}
        if(actual!=exp){
            input.setstate(ios::failbit);
        }
        return input;
    }
    
    std::istream& operator>> (std::istream& input , NumberWithUnits& c){
    double temp = 0;
    string unit;
    ios::pos_type star = input.tellg();
    if((!(input>>temp))||(!getAndCheckNextChar(input, '['))||(!(input>>unit))){
        auto errorState = input.rdstate();
        input.clear();
        input.seekg(star);
        input.clear(errorState);

    }
    else{
        if(unit.at(unit.length()-1)==']'){
            unit = unit.substr(0,unit.length()-1);
        }
        else{
            getAndCheckNextChar(input,']');
        }
        if(list.find(unit)==list.end()||unit.length()==0||sizeof(temp)==0){
            throw out_of_range{"hi"};
        }
        c.sizeUnit = unit;
        c.num = temp;
    }
    return input;
}
}

