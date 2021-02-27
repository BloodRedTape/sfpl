#include <cmath>
#include <sstream>
#include <iomanip>
#include "utils.hpp"

namespace libplot{
namespace Utils{

char PostfixTable[] = {
    'k',
    'm',
    'b',
    't'
};

float PowerTable[] = {
    1000.f,
    1000000.f,
    1000000000.f,
    1000000000000.f
};

std::string Shorten(double n){
    char postfix = 0;
    for(size_t i = sizeof(PostfixTable); i>0; --i){
        if(fabs(n) > PowerTable[i - 1]){
            n/=PowerTable[i - 1];
            postfix = PostfixTable[i - 1];
            break;
        }
    }
    std::stringstream ss;
    ss << std::setw(3 + (postfix == 0)) << std::ceil(n) << postfix;
    return ss.str();
}

}//namespace Utils::
}//namespace libplot::