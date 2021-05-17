
#include "pwmath.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>

namespace pw{

int factorial(int n) 
{
  return (n == 1 || n ==0 ) ? 1 : factorial(n-1)*n;
}

double getMin(const std::vector<double>& vec){
    auto min_iter = std::min_element(std::begin(vec),std::end(vec));
    return *min_iter;
}

double getMax(const std::vector<double>& vec){
    auto max_iter = std::max_element(std::begin(vec),std::end(vec));
    return *max_iter;
}

bool isInteger(const std::string& s)
{
    return (s.find_first_not_of("0123456789") == std::string::npos);
}

bool rowIsIntegers(const std::vector<std::string>& row){
    if(row.empty())
        return false;
    for(unsigned int i = 0; i < row.size(); i++){
        if(!isInteger(row[i]))
            return false;
    }
    return true;
}

bool isDouble(const std::string& s){
    std::istringstream iss(s);
    double d;
    return iss >> d && !iss.ignore();
}

bool rowIsDoubles(const std::vector<std::string>& row){
    if(row.empty())
        return false;
    for(unsigned int i = 0; i < row.size(); i++){
        if(!isDouble(row[i]))
            return false;
    }
    return true;
}

double getMin(int sz,double* x){
  double min_val = x[0];
  for(int i = 1; i < sz; i++){
      if(x[i] < min_val)
          min_val = x[i];
  }
  return min_val;
}

double getMax(int sz,double* x){
  double max_val = x[0];
  for(int i = 1; i < sz; i++){
      if(x[i] > max_val)
          max_val = x[i];
  }
  return max_val;
}

double getMax(const dcmplx* arr,int size)
{
    double maxVal = 0.0; 
    double temp = 0.0; 
    for(int i = 0; i < size; i++){
        temp = std::norm(arr[i]);
        maxVal = std::max(temp,maxVal); 
    }
    return maxVal;
}



}


