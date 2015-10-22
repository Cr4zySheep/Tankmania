#ifndef LOADER_HPP_INCLUDED
#define LOADER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>

template<typename T>
class Loader {
private:
    std::map<sf::String, T> data;
    T byDefault;

public:
    Loader() {
    };

    void load(sf::String const& name, sf::String const& filename) {
        T rsc;
        if(rsc.loadFromFile(filename)) {
            data[name] = rsc;
        }
        return;
    };

    T& getRef(sf::String const& name) {
        return (data.find(name) != data.end()) ? data.at(name) : byDefault;
    };


};

#endif // LOADER_HPP_INCLUDED
