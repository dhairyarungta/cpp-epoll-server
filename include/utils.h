#pragma once
#include <unordered_map>
#include <string>
#include <map>




enum class HttpMethod :int
{
    OPTIONS = 0, 
    GET,
    POST, 
    // SIZE,
};

static std::unordered_map<std::string,HttpMethod> method_to_enum{
    {"OPTIONS", HttpMethod::OPTIONS },
    {"GET", HttpMethod::GET},
    {"POST", HttpMethod::POST},
};


const std::string WHITESPACE = " \n\r\t\f\v";

inline std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start==std::string::npos) ? "" : s.substr(start);

}

inline std::string rtrim (const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end==std::string::npos) ? "" : s.substr(0,end+1);

}

inline std::string trim(const std::string &s)
{
    return rtrim(ltrim(s));

}

const std::string LINE_SEP = "\r\n";
using SSMap = std::map<std::string, std::string>;
