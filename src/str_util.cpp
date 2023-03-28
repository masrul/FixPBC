/**
 * @author      : Masrul Huda (mail2masrul@gmail.com)
 * @file        : str_util
 * @created     : Saturday Sep 10, 2022 03:02:16 CDT
 */

#ifndef STR_UTIL_HPP

#define STR_UTIL_HPP

#include "str_util.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

namespace StrUtil
{

const std::string WHITESPACE = " \n\r\t\f\v";
/* template<typename T> */
std::vector<size_t> extract_numbers(std::string str){
    std::vector<size_t> arr; 
    std::istringstream ss{str};
    size_t num; 
    while(ss>>num) 
        arr.push_back(num);
    return arr;
}

//https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/ 
std::string ltrim(const std::string &s){
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
std::string rtrim(const std::string &s){
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
std::string trim(const std::string &s){
    return rtrim(ltrim(s));
}


// https://stackoverflow.com/a/46931770/4957692
std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;
    while (getline (ss, item, delim)) 
        result.push_back (item);
    return result;
}
std::vector<std::string> split (const std::string &s) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;
    while (ss>>item) 
        result.push_back (item);
    return result;
}

std::string join(const std::vector<std::string>& vector_of_strings, char delim='-'){
    std::string result{}; 
    for(const auto& item : vector_of_strings)
        result +=(item+delim);
    result.erase(result.size()-1);
    return result;
}



} // namespace StrUtil 


#endif /* end of include guard STR_UTIL_HPP */

