#include "Gameplay.hpp"

Gameplay::Gameplay(Game* game) : map(textureManager)
{
    this->game = game;
    this->adapt_view_to_window();
    this->load_textures();
    map.create();

    tanks.push_back(new IA(textureManager, 1000, 1000));
    tankToFollow = tanks.size() - 1;
}

Gameplay::~Gameplay()
{
    while(!tanks.empty())
    {
        delete tanks.back();
        tanks.pop_back();
    }

    while(!bullets.empty())
    {
        delete bullets.back();
        bullets.pop_back();
    }
}

void Gameplay::handleInput()
{
    sf::Event event;

    while(game->window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            game->window.close();
            break;

        case sf::Event::Resized:
            this->adapt_view_to_window();
            break;

        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Escape) game->window.close();
            if(event.key.code == sf::Keyboard::Space)
            {
                game->changeState(new Gameplay(game));
            }
            break;
        }
    }

    for(auto& tank : tanks) tank->handleInput();
}

void Gameplay::update(float dt)
{
    if(dt > 1) dt = 1 / 60;
    //Récupération des obus
    for(auto tank : tanks)
    {
        Bullet* bullet = tank->getBullet();
        if(bullet != nullptr) bullets.push_back(bullet);
    }

    //Collisions
    for(auto tank : tanks) map.handle_collision(*tank, dt);
    for(uint a(0); a < bullets.size(); a++) if(map.handle_collision(*bullets[a], dt))
    {
        delete bullets[a];
        bullets.erase(bullets.begin() + a);
    }

    //Alignement canon / souris
    sf::Vector2i mouse = sf::Mouse::getPosition(game->window);
    //tanks[tankToFollow]->align_barrel(game->window.mapPixelToCoords(mouse));


    for(auto tank : tanks) tank->update(dt);
    for(auto bullet : bullets) bullet->update(dt);

    this->scrolling();
}

void Gameplay::draw()
{
    map.draw_below(game->window);
    for(auto tank : tanks)     tank->draw(game->window);
    for(auto bullet : bullets) bullet->draw(game->window);
    map.draw_above(game->window);
}

void Gameplay::adapt_view_to_window()
{
    view.reset(sf::FloatRect(0, 0, (float)game->window.getSize().x * 2, (float)game->window.getSize().y * 2));
    game->window.setView(view);
}

void Gameplay::scrolling()
{
    sf::Vector2u window = game->window.getSize();
    double tiles_x(window.x / 128),
           tiles_y(window.y / 128);

    Tank* tank = tanks[tankToFollow];
    sf::Vector2f center = tank->getPosition();

    if(tank->getPosition().x < tiles_x * 128) center.x = tiles_x * 128;
    else if(tank->getPosition().x > (map_width - tiles_x) * 128) center.x = (map_width - tiles_x) * 128;

    if(tank->getPosition().y < tiles_y * 128) center.y = tiles_y * 128;
    else if(tank->getPosition().y > (map_height - tiles_y) * 128) center.y = (map_height - tiles_y) * 128;

    view.setCenter(center);

    game->window.setView(view);
}

void Gameplay::load_textures()
{
    //Sols
    textureManager.loadTexture("dirt", "rsc/Environment/dirt.png");
    textureManager.loadTexture("grass", "rsc/Environment/grass.png");

    //Tanks
    textureManager.loadTexture("tankBeige", "rsc/Tanks/tankBeige_outline.png");
    textureManager.loadTexture("barrelBeige", "rsc/Tanks/barrelBeige_outline.png");

    //Obstacles
    textureManager.loadTexture("barrelSide", "rsc/Obstacles/barrelGreen_side.png");
    textureManager.loadTexture("barrelUp", "rsc/Obstacles/barrelGreen_up.png");

    //Décors
    textureManager.loadTexture("oil", "rsc/Obstacles/oil.png");
    textureManager.loadTexture("treeLarge", "rsc/Environment/treeLarge.png");
    textureManager.loadTexture("treeSmall", "rsc/Environment/treeSmall.png");

    //Munitions
    textureManager.loadTexture("bulletBeige", "rsc/Bullets/bulletBeige_outline.png");
}
