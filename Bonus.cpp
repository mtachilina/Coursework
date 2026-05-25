#include "Bonus.h"

Bonus::Bonus(float x, float y, int t)
{
    type = t;
    vel = { 0.f, 2.f };

    if (type == 5)
    {
        isCircle = true;

        circle = sf::CircleShape(10.f);
        circle.setFillColor(sf::Color::White);
        circle.setPosition(x, y);
    }
    else
    {
        isCircle = false;

        poly = sf::ConvexShape();
        poly.setPointCount(4);

        poly.setPoint(0, { 10.f, 0.f });
        poly.setPoint(1, { 20.f, 10.f });
        poly.setPoint(2, { 10.f, 20.f });
        poly.setPoint(3, { 0.f, 10.f });

        poly.setPosition(x, y);

        if (type == 1)
            poly.setFillColor(sf::Color::Green);
        else if (type == 2)
            poly.setFillColor(sf::Color::Yellow);
        else if (type == 3)
            poly.setFillColor(sf::Color(180, 0, 255));
        else if (type == 4)
            poly.setFillColor(sf::Color::Blue);
        else
            poly.setFillColor(sf::Color::Cyan);
    }
}

void Bonus::update()
{
    if (isCircle)
        circle.move(vel);
    else
        poly.move(vel);
}

sf::FloatRect Bonus::getBounds() const
{
    return isCircle ? circle.getGlobalBounds() : poly.getGlobalBounds();
}

void Bonus::draw(sf::RenderWindow& window)
{
    if (isCircle)
        window.draw(circle);
    else
        window.draw(poly);
}