#ifndef SFPL_TESTS_COMMON_HPP
#define SFPL_TESTS_COMMON_HPP

namespace sfpl{

struct FunctionRange{
    const char *Name;
    double Begin;
    double End;
    double Step;
    double (*Proc)(double);
};

extern const FunctionRange s_TestFunctionRanges[21];

}//namespace sfpl::

#endif //SFPL_TESTS_COMMON_HPP