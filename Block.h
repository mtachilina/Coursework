#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include "Ball.h"

class Block
{
public:
    sf::RectangleShape shape;
    int type;
    int hp;
    bool alive;

    Block(float x, float y, int t);
};

#endif
