
#include "pwutils/pwmath.hpp"
#include <algorithm>
#include <string>
#include <cmath>
#include <stdexcept>

namespace pw{

int factorial(int n) 
{
  return (n == 1 || n ==0 ) ? 1 : factorial(n-1)*n;
}

bool isInteger(const std::string& s)
{
    try{
        int val = std::stoi(s);
    }
    catch(std::exception& e){
        return false;
    }
    return true;
}

bool rowIsIntegers(const std::vector<std::string>& row){
    if(row.empty())
        return false;
    for(const auto& item : row)
        if(!isInteger(item))
            return false;
    return true;
}

bool isDouble(const std::string& s){
    try{
        double val = std::stod(s);
    }
    catch(std::exception& e){
        return false;
    }
    return true;
}

bool rowIsDoubles(const std::vector<std::string>& row){
    if(row.empty())
        return false;
    for(const auto& item : row)
        if(!isDouble(item))
            return false;
    return true;
}



}


