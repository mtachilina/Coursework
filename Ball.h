#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball
{
public:
    sf::CircleShape shape;
    sf::Vector2f vel;

    Ball(float x, float y);
    void update();
    void bounceX();
    void bounceY();
};

#endif