#include "Block.h"

Block::Block(float x, float y, int t)
{
    type = t;
    hp = (t == 4) ? 5 : 1;
    alive = true;
    shape = sf::RectangleShape(sf::Vector2f(80, 25));
    shape.setPosition(x, y);
    if (t == 1) shape.setFillColor(sf::Color(120, 120, 120));
    else if (t == 2) shape.setFillColor(sf::Color::Cyan);
    else if (t == 3) shape.setFillColor(sf::Color::Yellow);
    else shape.setFillColor(sf::Color(199, 21, 133));
}

void Block::onHit(Ball& ball, int& score)
{
}