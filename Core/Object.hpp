#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include "CollisionManager.hpp"
#include <iostream>
constexpr float PI = 3.1415927;

class Object
{
protected:
    /* Côté graphique */
    sf::Sprite sprite;
    uint width;
    uint height;


    /* Gestion des collisions */
    bool collision; //Une collision a eu lieu
    CollisionData collisionData;

    /* Gestion des déplacement */
    float velocity;  //Vitesse
    float direction; //Direction
                     //Permet de calculer le vecteur de mouvement
    sf::Vector2f motion_vector; //Vecteur de mouvement

    void calculate_MotionVector();
    void move(float dt);

public:
    Object();
    Object(sf::Texture const& texture, float x, float y, unsigned int width, unsigned int height);
    virtual ~Object();

    //Définit la position du sprite
    void setPosition(float x, float y);
    //Définit l'origine du sprite en son centre
    void setOrigin(unsigned int width, unsigned int heigth);
    //Définit et ajuste la texture à la taille du sprite
    void setTexture(sf::Texture const& texture, unsigned int w, unsigned int h);

    virtual void handleInput() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    sf::Vector2f getOrigin() const;
    sf::Vector2f getPosition() const;

    CollisionData getCollisionData(float dt);
    float left() const;
    float top() const;
    float getVelocity() const;
    float getWidth() const;
    float getHeight() const;

    void activeCollision();

    void change_direction(float const new_direction);
    void change_velocity(float const new_velocity);
    void change_movement(float const new_direction, float const new_velocity);

    bool isMovingToRight() const;
    bool isMovingToLeft() const;
    bool isMovingToTop() const;
    bool isMovingToBottom() const;

    sf::Vector2f getMotionVector() const;
};

#endif // OBJECT_HPP_INCLUDED
