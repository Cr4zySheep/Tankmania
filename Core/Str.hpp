#ifndef STR_HPP_INCLUDED
#define STR_HPP_INCLUDED

#include <sstream>
#include <SFML/System.hpp>

class Str {
public:
    static sf::String convert(int a) {
        std::stringstream ss;
        ss << a;
        return sf::String(ss.str());
    }
};

#endif // STR_HPP_INCLUDED
