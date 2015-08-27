#include "IA.hpp"

IA::IA(TextureManager &textureManager, float x, float y) : Tank(textureManager, x, y)
{
    state.type = IA_WAIT;
}

IA::~IA()
{

}

void IA::handleInput()
{
    if(state.type == IA_FOLLOW_PATH)
    {
        //Raccourcis
        Point destination = state.data.path.destination;
        std::vector<Point>& path = state.data.path.path;

        if(!path.empty())
        {
            Point& point = path.back();
            float angle = atan2(point.y - this->getPosition().y, point.x - this->getPosition().x) * 180 / PI * -1;

            /* float diff(abs(angle - direction)), move;
            if(diff > 3) move = 3;
            else         move = diff;

            if(angle < direction) this->change_direction(direction + move * -1);
            else                  this->change_direction(direction + move);*/

            this->change_direction(angle);

            //Arrivé à destination ?
            if(Point::distance(this->getPosition(), destination) <= 16)
            {
                state.type = IA_WAIT;
            }

            //Encore loin du prochain point ?
            if(Point::distance(Point(this->getPosition()), point) > 300)
            {
                velocity += 10;
            }
            //Ou on peut passer au suivant ?
            else if(Point::distance(Point(this->getPosition()), point) <= 16)
            {
                velocity -= 10;
                path.pop_back();
            }
            else velocity += 10;
        }
        else
        {
            state.type = IA_WAIT;
        }
    }
    else if(state.type == IA_SEARCH_PATH)
    {
        state.data.path.path = Pathfinding::find_path(Pathfinding::convert_pos(this->getPosition()), Pathfinding::convert_pos(sf::Vector2f(state.data.path.destination.x, state.data.path.destination.y)));
        state.type = IA_FOLLOW_PATH;
    }
    else if(state.type == IA_WAIT)
    {
        if(velocity > 0) {
            velocity -= 10;
            if(velocity < 0) velocity = 0;
        }
        if(velocity == 0) {
            state.type = IA_SEARCH_PATH;
            state.data.path.destination = Point({rand() % 128 * 30, rand() % 128 * 30});
            state.data.path.path = std::vector<Point>();
        }
    }

    this->regulate_velocity();
    this->calculate_MotionVector();
}

void IA::update(float dt)
{
    if(collision) {
        state.data.path.path.clear();
        state.type = IA_WAIT;
        collision = false;
    }

    this->move(dt);

    update_barrel();
    if(bullet != 0) bullet->update(dt);
}
