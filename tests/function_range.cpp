#include <cmath>
#include <cstdlib>
#include "function_range.hpp"

namespace sfpl{

const FunctionRange s_TestFunctionRanges[21]={
    {
        "Presice",
        -212,  232,    2,                
        [](double x){return (x*x)/1000 + 2000000000;}
    },
    {
        "Simple",
        -4,    4,      1,                  
        [](double x){return x*x + 3;}
    },
    {
        "ToAlign",
        -3,    312,    5,                
        [](double x){return x*x;}
    },
    {
        "HighRes",
        -41,   41,     1,                
        [](double x)->double{return x*x*10000 + std::pow(12434,2);}
    },
    {
        "Random",
        -43,   43,     1,            
        [](double x)->double{return std::rand()%2000;}
    },
    {
        "LowLevel2",
        -0.234,0.127,  0.01,       
        [](double x){return x*x;}
    },
    {
        "LowLevel",
        -0.9,  0.9,    0.01,             
        [](double x){return x*x;}
    },
    {
        "Parabola",
        -10,   10,     0.4,             
        [](double x){return x*x;}
    },
    {
        "A Lot",
        0,     20000000, 4,             
        [](double x)->double{return std::sqrt(x);}
    },
    {
        "Line",
        0,     20000234, 4,             
        [](double x){return x + 124;}
    },
    {
        "A Lot 2",
        0,     2000000, 4,             
        [](double x){return x*x;}
    },
    {
        "Parabola 9",
        0,     9,      1, 
        [](double x){return x*x;}
    },
    {
        "Parabola 6",
        0,     6,      1, 
        [](double x){return x*x;}
    },
    {
        "Parabola 5",
        0,     5,      1, 
        [](double x){return x*x;}
    },
    {
        "Parabola 4",
        0,     4,      1, 
        [](double x){return x*x;}
    },
    {
        "Dungeon Master",
        0,     200,    1, 
        [](double i)->double{return i * (long(i) % 13) * 11 / ((long(i)/3 + 256) * 7) * (-1 + (long(i)%2)*2);}
    },
    {
        "Math",
        0,     100,    0.1, 
        [](double x)->double{return std::sin(x)*2 + 3.14/4 + std::cos(x/10) + std::sin(x/4);}
    },
    {
        "Fish",
        0,     200,    1, 
        [](double i)->double{return std::sin(i * 3.1415926535/180) * (-1 + (long(i)%2)*2);}
    },
    {
        "Kind of wave",
        0,     200,    0.1, 
        [](double x)->double{return std::sin(x) + (long(x)%20)*3;}
    },
    {
        "Heart",
        -4,    4,      0.01, 
        [](double x)->double{
            double a = 0.2, d = 1.4, h = 3, s = 0.05, w = 0.02;
            double e = 2.71;
            double L = 2*d;
            x = x - std::ceil(x/L - 0.5)*L;
            return a*(std::pow(e,((-std::pow((x + d),2)) / (2*w))) + std::pow(e,((-std::pow((x - d),2)) / (2*w)))) + (h - std::abs(x / s) - x) * std::pow(e,((-std::pow((7*x),2)) / 2));
        }
    },
    {
        "Negative",
        -200,  0,      1, 
        [](double x)->double{return sqrt(std::fabs(x));}
    },
};

}//namespace sfpl::