#include "Ball.h"

Ball::Ball(float x, float y)
{
    shape = sf::CircleShape(8.f);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
    vel = sf::Vector2f(3.f, -3.f);
}

void Ball::update()
{
    shape.move(vel);
}
