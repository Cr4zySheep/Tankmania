#ifndef STR_HPP_INCLUDED
#define STR_HPP_INCLUDED

#include <sstream>

class Str {
public:
    static std::string convert(int a) {
        std::stringstream ss;
        ss << a;
        return ss.str();
    }
};

#endif // STR_HPP_INCLUDED
