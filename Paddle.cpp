#include "Paddle.h"

Paddle::Paddle()
{
    shape = sf::RectangleShape(sf::Vector2f(100, 15));
    shape.setPosition(400, 570);
    shape.setFillColor(sf::Color::Green);
    speed = 7.f;
}

void Paddle::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (shape.getPosition().x > 0)
            shape.move(-speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (shape.getPosition().x + shape.getSize().x < 900)
            shape.move(speed, 0);
    }
}

void Paddle::setSize(float width)
{
    float x = shape.getPosition().x;
    shape.setSize(sf::Vector2f(width, 15));
    if (x + width > 900)
        shape.setPosition(900 - width, 570);
}