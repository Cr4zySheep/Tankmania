#include "GameMode.hpp"

GameMode::GameMode(Game* game) : map(textureManager)
{
    this->game = game;
    this->adapt_view_to_window();
    this->load_textures();
    map.create();

    game->window.create(sf::VideoMode::getFullscreenModes()[0], "Tankmania", sf::Style::Fullscreen);
    this->adapt_view_to_window();
}

GameMode::~GameMode()
{
    for(auto& tank : tanks)
    {
        delete tank.second;
    }

    while(!bullets.empty())
    {
        delete bullets.back();
        bullets.pop_back();
    }
}

void GameMode::handleInput()
{
    Pathfinding::enable = true;

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
            if(event.key.code == sf::Keyboard::Space) {this->finish(); return;} //DO NOT forget to remove later
            break;
        }
    }

    for(auto& tank : tanks) tank.second->handleInput();
}

void GameMode::draw()
{
    //Display game
    map.draw_below(game->window);
    for(auto& tank : tanks)    tank.second->draw(game->window);
    for(auto bullet : bullets) bullet->draw(game->window);
    map.draw_above(game->window);
}

void GameMode::align_player_barrel()
{
    //Alignement canon / souris
    sf::Vector2i mouse = sf::Mouse::getPosition(game->window);
    tanks[mainPlayer]->align_barrel(game->window.mapPixelToCoords(mouse));
}

void GameMode::handleCollision(Tank* tank, float dt)
{
    map.handle_collision(*tank, dt);
    for(int a(bullets.size() - 1); a >= 0; a--)
    {
        if(map.handle_collision(*bullets[a], dt) || !bullets[a]->alive())
        {
            delete bullets[a];
            bullets.erase(bullets.begin() + a);
        }
        else if(CollisionManager::collide(*tank, *bullets[a], dt, false) &&
                tank->name != bullets[a]->shooter &&
                (tank->team != bullets[a]->team || bullets[a]->team == NO_TEAM))
        {
            if(!tank->isDestroyed()) if(tank->damaged(bullets[a])) kills.push({bullets[a]->shooter, tank->name, bullets[a]->team});
            delete bullets[a];
            bullets.erase(bullets.begin() + a);
        }
    }
    for(auto& i : tanks) if(i.second->name != tank->name) CollisionManager::collide(*i.second, *tank, dt);
}

sf::Vector2f GameMode::generate_pos()
{
    for(;;)
    {
        sf::Vector2f pos({rand() % 128 * 30, rand() % 128 * 30});
        if(Pathfinding::graph[Pathfinding::convert_pos(pos)].obstacle == false) return pos;
    }
}

void GameMode::update_bullets(float dt)
{
    for(int a(bullets.size() - 1); a >= 0; a--) bullets[a]->update(dt);
}

void GameMode::get_bullet(Tank* tank)
{
    //Récupération des obus
    Bullet* bullet = tank->getBullet();
    if(bullet != nullptr) bullets.push_back(bullet);
}

void GameMode::limit_dt(float& dt)
{
    if(dt > 0.08) dt = 1 / 60;
}

void GameMode::adapt_view_to_window()
{
    view.reset(sf::FloatRect(0, 0, (float)game->window.getSize().x * 2, (float)game->window.getSize().y * 2));
    game->window.setView(view);
}

void GameMode::scrolling()
{
    sf::Vector2u window = game->window.getSize();
    double tiles_x((double)window.x / 128),
           tiles_y((double)window.y / 128);

    Tank* tank = tanks[tankToFollow];
    sf::Vector2f center = tank->getPosition();

    if(tank->getPosition().x < tiles_x * 128) center.x = tiles_x * 128;
    else if(tank->getPosition().x > (map_width - tiles_x) * 128) center.x = (map_width - tiles_x) * 128;

    if(tank->getPosition().y < tiles_y * 128) center.y = tiles_y * 128;
    else if(tank->getPosition().y > (map_height - tiles_y) * 128) center.y = (map_height - tiles_y) * 128;

    view.setCenter(center);

    game->window.setView(view);
}

void GameMode::load_textures()
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

    //Fonts
    fontManager.loadFont("thickhead", "rsc/fonts/thickhead.ttf");
}

void GameMode::finish() {
    std::map<sf::String, sf::Color> colors;
    for(auto& tank : tanks) if(!tank.first.isEmpty()) {
        colors[tank.first] = tank.second->getColorName();
    }

    game->changeState(new Scoreboard(game, scores, colors));
}
