#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle
{
public:
    sf::RectangleShape shape;
    float speed;

    Paddle();
    void update();
    void setSize(float width);
};

#endif