/**
 * @author      : Masrul Huda (mail2masrul@gmail.com)
 * @file        : math_util
 * @created     : Monday Oct 03, 2022 23:24:00 CDT
 */

#ifndef MATH_UTIL_HPP

#define MATH_UTIL_HPP

#include<vector>
#include<cmath>

namespace MathUtil 
{ 

std::vector<float> CrossProduct(std::vector<float> const &a, std::vector<float> const &b){
    std::vector<float> r (a.size());  
    r[0] = a[1]*b[2]-a[2]*b[1];
    r[1] = a[2]*b[0]-a[0]*b[2];
    r[2] = a[0]*b[1]-a[1]*b[0];
    return r;
}

float  DotProduct(std::vector<float> const &a, std::vector<float> const &b){
    float dot  = 0.0; 
    for (auto i=0; i<3;++i)
        dot += (a[i]*b[i]);
    return dot; 
}

void UnitVector(std::vector<float>& a){

    float sum = 0.0; 
    for (const auto& item : a)
        sum +=(item*item);
    sum=sqrt(sum);

    for (auto& item : a)
        item /= sum;
}

float norm(const std::vector<float>& a){
    float sum = 0.0; 
    for (const auto& item : a)
        sum +=(item*item);
    sum=sqrt(sum);
    return sum; 
}

float  CosAngle(std::vector<float> const &a, std::vector<float> const &b){
    return DotProduct(a,b)/norm(a)/norm(b);
}

std::vector<float> Add(std::vector<float> const &a, std::vector<float> const &b){
    std::vector<float> r (a.size());  
    
    for (auto i=0; i<a.size(); ++i)
        r[i] = a[i] + b[i];
    return r;
}

std::vector<float> Subtract(std::vector<float> const &a, std::vector<float> const &b){
    std::vector<float> r (a.size());  
    
    for (auto i=0; i<a.size(); ++i)
        r[i] = a[i] - b[i];
    return r;
}

} // end MathUtil 

#endif /* end of include guard MATH_UTIL_HPP */

