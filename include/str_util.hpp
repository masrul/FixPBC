/**
 * @author      : Masrul Huda (mail2masrul@gmail.com)
 * @file        : str_util
 * @created     : Saturday Sep 10, 2022 03:02:16 CDT
 */

#ifndef STR_UTIL_HPP

#define STR_UTIL_HPP

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


namespace StrUtil
{

/* template<typename T> */ 
std::vector<size_t> extract_numbers(std::string);

std::string ltrim(const std::string&);
std::string rtrim(const std::string&);
std::string trim(const std::string&);


std::vector<std::string> split (const std::string&, char);
std::vector<std::string> split (const std::string &);

std::string join(const std::vector<std::string>&, char);



} // namespace StrUtil 


#endif /* end of include guard STR_UTIL_HPP */

