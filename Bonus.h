#pragma once
#include <SFML/Graphics.hpp>

class Bonus
{
public:
    Bonus(float x, float y, int type);

    void update();
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

    bool active = true;
    int type;

    sf::CircleShape circle;
    sf::ConvexShape poly;
    bool isCircle = false;

    sf::Vector2f vel = { 0.f, 2.f };
};