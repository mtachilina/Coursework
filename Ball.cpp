#include "Ball.h"

Ball::Ball(float x, float y)
{
    shape = sf::CircleShape(8.f);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
    vel = sf::Vector2f(2.5f, -2.5f);
}

void Ball::update()
{
    shape.move(vel);
}

void Ball::bounceX()
{
    vel.x = -vel.x;
}

void Ball::bounceY()
{
    vel.y = -vel.y;
}