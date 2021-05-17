
#ifndef PWMATH_H_ 
#define PWMATH_H_

#include <string>
#include <vector>
#include "pwconstants.h"

namespace pw{

    double getMax(const dcmplx* arr,int sz);
    double getMin(double* x, int sz);
    double getMax(double* x, int sz);
    double getMin(const std::vector<double>& vec);
    double getMax(const std::vector<double>& vec);
    int factorial(int);

    bool isInteger(const std::string& s);
    bool rowIsIntegers(const std::vector<std::string>& row);
    bool isDouble(const std::string& s);
    bool rowIsDoubles(const std::vector<std::string>& row);


    inline int isinf(double x)
    {
       if ((x == x) && ((x - x) != 0.0)) return (x < 0.0 ? -1 : 1);
       else return 0;
    }

    inline int isnan(double x)
    {
       return x != x;
    }
}

#endif


