#ifndef IA_HPP_INCLUDED
#define IA_HPP_INCLUDED

#include "IA_Moving.hpp"
#include "IA_Follow.hpp"
#include "IA_Shoot.hpp"
#include "IA_Think.hpp"

class IA : public Tank
{
public:
    IA_Moving moving;
    IA_Follow follow;
    IA_Shoot shoot;
    IA_Think think;
    std::map<std::string, Tank*>& tanks;

    IA(TextureManager& textureManager, float x, float y, std::string const name, int const _team, std::map<std::string, Tank*>& _tanks);
    virtual ~IA();

    void handleInput();
    void update(float dt);
};

#endif // IA_HPP_INCLUDED
