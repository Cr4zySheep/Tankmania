#include "IA_Moving.hpp"

IA_Moving::IA_Moving() : state(IA_WAIT)
{

}

void IA_Moving::update(Tank* tank)
{
    if(state == IA_SEARCH_PATH)
    {
        path = Pathfinding::find_path(Pathfinding::convert_pos(tank->getPosition()), Pathfinding::convert_pos(sf::Vector2f(destination.x, destination.y)));
        state = IA_FOLLOW_PATH;
    }

    if(state == IA_FOLLOW_PATH)
    {
        if(!path.empty())
        {
            Point& point = path.back();
            float angle = atan2(point.y - tank->getPosition().y, point.x - tank->getPosition().x) * 180 / PI * -1;

            tank->change_direction(angle);

            //Arrivé à destination ?
            if(Point::distance(tank->getPosition(), destination) <= 16)
            {
                state = IA_WAIT;
            }

            //Peut-on passer au suivant ?
            if(Point::distance(Point(tank->getPosition()), point) <= 16)
            {
                tank->change_velocity(tank->getVelocity() - 10);
                path.pop_back();
            }
            else tank->change_velocity(tank->getVelocity() + 10);
        }
        else
        {
            state = IA_WAIT;
        }
    }
    else if(state == IA_WAIT)
    {
        float velocity = tank->getVelocity();
        if(velocity > 0) {
            tank->change_velocity(tank->getVelocity() - 10);
            if(velocity < 0) tank->change_velocity(0);
        }
        else if(velocity < 0)
        {
            tank->change_velocity(tank->getVelocity() + 10);
            if(velocity > 0) tank->change_velocity(0);
        }
    }
}

void IA_Moving::go_to(Point point)
{
    destination = point;
    state = IA_SEARCH_PATH;
}

void IA_Moving::stop()
{
    path.clear();
    state = IA_WAIT;
}
