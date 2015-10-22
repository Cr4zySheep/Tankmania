#include "GameMode.hpp"

GameMode::GameMode(Game* game) : map(textureLoader)
{
    this->game = game;
    this->adapt_view_to_window();
    this->load_textures();
    map.create();
    BulletsManager::eraseAllBullets();
    cursor.setTexture(textureLoader.getRef("cursor"));
    cursor.setOrigin(16, 16);
    waitedTime = sf::seconds(5.f);

    game->window.create(sf::VideoMode::getFullscreenModes()[0], "Tankmania", sf::Style::Fullscreen);
    this->game->window.setMouseCursorVisible(false);
    this->adapt_view_to_window();
}

GameMode::~GameMode()
{
    for(auto& tank : tanks)
    {
        delete tank.second;
    }

    BulletsManager::eraseAllBullets();
}

void GameMode::handleInput()
{
    if(waitedTime.asSeconds() > 0) return;
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
            if(event.key.code == sf::Keyboard::Space) { this->finish(); return;} //DO NOT forget to remove later
            break;
        }
    }

    for(auto& tank : tanks) tank.second->handleInput();

    cursor.setPosition(game->window.mapPixelToCoords(sf::Mouse::getPosition()));
}

void GameMode::draw()
{
    //Display game
    map.draw_below(game->window);
    for(auto& tank : tanks)    tank.second->draw(game->window);
    BulletsManager::draw(game->window);
    map.draw_above(game->window);

    //Display cursor
    game->window.draw(cursor);
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
    for(int a(BulletsManager::bulletsCount() - 1); a >= 0; a--)
    {
        Bullet& bullet = BulletsManager::getBullet(a);
        if(map.handle_collision(bullet, dt))
        {
            BulletsManager::removeBullet(a);
        }
        else if(CollisionManager::collide(*tank, bullet, dt, false) &&
                tank->name != bullet.getShooter() &&
                (tank->team != bullet.getTeam() || bullet.getTeam() == NO_TEAM))
        {
            if(!tank->isDestroyed()) if(tank->damaged(bullet)) kills.push({bullet.getShooter(), tank->name, bullet.getTeam()});
            BulletsManager::removeBullet(a);
        }
    }
    for(auto& i : tanks) if(i.second->name != tank->name) CollisionManager::collide(*i.second, *tank, dt);
}

sf::Vector2f GameMode::generate_pos()
{
    for(;;)
    {
        sf::Vector2f pos({rand() % 128 * 30, rand() % 128 * 30});
        if(Pathfinding::enough_place(Pathfinding::convert_pos(pos))) {
            if(!tanks.empty()) {
                for(auto tank : tanks) if(Point::distance(Point(tank.second->getPosition()), Point(pos)) > 150*150) return pos;
            } else {
                return pos;
            }
        }
    }
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
    textureLoader.load("dirt", "rsc/Environment/dirt.png");
    textureLoader.load("grass", "rsc/Environment/grass.png");

    //Tanks
    textureLoader.load("tankBeige", "rsc/Tanks/tankBeige_outline.png");
    textureLoader.load("barrelBeige", "rsc/Tanks/barrelBeige_outline.png");

    //Obstacles
    textureLoader.load("barrelSide", "rsc/Obstacles/barrelGreen_side.png");
    textureLoader.load("barrelUp", "rsc/Obstacles/barrelGreen_up.png");

    //Décors
    textureLoader.load("oil", "rsc/Obstacles/oil.png");
    textureLoader.load("treeLarge", "rsc/Environment/treeLarge.png");
    textureLoader.load("treeSmall", "rsc/Environment/treeSmall.png");

    //Munitions
    textureLoader.load("bulletBeige", "rsc/Bullets/bulletBeige_outline.png");

    //Fonts
    fontLoader.load("thickhead", "rsc/fonts/thickhead.ttf");

    //Cursor
    textureLoader.load("cursor", "rsc/crosshair32.png");
}

void GameMode::finish() {
    std::map<sf::String, sf::Color> colors;
    for(auto& tank : tanks) if(!tank.first.isEmpty()) {
        colors[tank.first] = tank.second->getColorName();
    }

    game->changeState(new Scoreboard(game, scores, colors));
}

bool GameMode::updateWaitedTime(float dt) {
    if(waitedTime.asSeconds() > 0) {
        waitedTime -= sf::seconds(dt);
        return false;
    }
    return true;
}
