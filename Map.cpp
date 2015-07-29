#include "Map.hpp"
using std::cout;
using std::endl;

Map::Map()
{

}

Map::~Map()
{

}

void Map::create(TextureManager& textureManager)
{
    for(auto x(0); x < map_width; x++) for(auto y(0); y < map_height; y++)
    {
        auto iterator(x * map_width + y);

        tiles[iterator].setTexture(textureManager.getRef("dirt"));
        tiles[iterator].setPosition(x * 128, y * 128);
    }

    auto limite_x(map_width * 128 / 48),
         limite_y(map_height * 128 / 48);
    for(auto x(0); x < limite_x; x++)
    {
        barrels.push_back(Barrel(textureManager, true, 24 + x * 48, 24, true));
        barrels.push_back(Barrel(textureManager, true, 24 + x * 48, limite_y * 48 - 24, true));
    }

    for(auto y(1); y < limite_y - 1; y++)
    {
        barrels.push_back(Barrel(textureManager, true, 24, 24 + y * 48, true));
        barrels.push_back(Barrel(textureManager, true, limite_x * 48 - 24, 24 + y * 48, true));
    }

    barrels.push_back(Barrel(textureManager, true, 500, 500, true));
    barrels.back().destroy();
}

void Map::draw(sf::RenderWindow& window)
{
    for(auto& tile : tiles) window.draw(tile);
    for(auto& barrel : barrels) barrel.draw(window);
}

void Map::handle_collision(Tank& tank, float dt)
{
    for(auto& barrel : barrels) if(!barrel.isDestroyed()) CollisionManager::collide(tank, barrel, dt);
}
