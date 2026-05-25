#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>

static void resolveCollision(sf::CircleShape& ball, sf::Vector2f& vel, sf::FloatRect rect)
{
    sf::FloatRect b = ball.getGlobalBounds();

    float dx = (b.left + b.width / 2) - (rect.left + rect.width / 2);
    float dy = (b.top + b.height / 2) - (rect.top + rect.height / 2);

    float overlapX = (b.width / 2 + rect.width / 2) - std::abs(dx);
    float overlapY = (b.height / 2 + rect.height / 2) - std::abs(dy);

    if (overlapX < overlapY)
    {
        ball.move((dx > 0 ? overlapX : -overlapX), 0);
        vel.x *= -1;
    }
    else
    {
        ball.move(0, (dy > 0 ? overlapY : -overlapY));
        vel.y *= -1;
    }
}

Game::Game() : window(sf::VideoMode(900, 600), "Arkanoid")
{
    window.setFramerateLimit(60);

    font.loadFromFile("LCD5x8HRU.ttf");

    infoText.setFont(font);
    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(10, 560);

    srand((unsigned)time(0));

    lives = 3;
    score = 0;

    shield = false;
    sticky = false;
    stickyTimer = 0.f;

    balls.push_back(Ball(450, 450));
    spawnBlocks();
}

void Game::spawnBlocks()
{
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 10; j++)
        {
            blocks.push_back(Block(10 + j * 89, 30 + i * 30, rand() % 4 + 1));
        }
      
}

void Game::spawnBonus(float x, float y, int type)
{
    bonuses.push_back(Bonus(x, y, type));
}

void Game::resetBall(Ball& b)
{
    b.shape.setPosition(450, 450);
    b.vel = sf::Vector2f(3.f, -3.f);
}

void Game::run()
{
    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::KeyPressed &&
                e.key.code == sf::Keyboard::Space)
            {
                for (auto& b : balls)
                {
                    if (std::abs(b.vel.x) < 0.01f && std::abs(b.vel.y) < 0.01f)
                        b.vel = sf::Vector2f(3.f, -3.f);
                }

                sticky = false;
            }
        }

        update();
        draw();
    }
}

void Game::update()
{
    if (sticky)
    {
        stickyTimer -= 1.f / 60.f;
        if (stickyTimer <= 0)
            sticky = false;
    }

    paddle.update();

    for (size_t i = 0; i < balls.size(); i++)
    {
        Ball& b = balls[i];
        b.update();

        sf::Vector2f pos = b.shape.getPosition();

        if (pos.x < 0) { pos.x = 0; b.vel.x *= -1; }
        if (pos.x > 900 - 16) { pos.x = 900 - 16; b.vel.x *= -1; }
        if (pos.y < 0) { pos.y = 0; b.vel.y *= -1; }

        if (pos.y > 600)
        {
            if (balls.size() > 1)
            {
                balls.erase(balls.begin() + i);
                i--;
                continue;
            }

            if (shield)
            {
                shield = false;
                resetBall(b);
                continue;
            }

            lives--;
            score--;

            if (lives <= 0)
            {
                window.close();
                return;
            }

            resetBall(b);
            continue;
        }

        b.shape.setPosition(pos);

        if (b.shape.getGlobalBounds().intersects(paddle.shape.getGlobalBounds()))
        {
            if (sticky)
            {
                b.vel = { 0.f, 0.f };
                b.shape.setPosition(
                    paddle.shape.getPosition().x + paddle.shape.getSize().x / 2 - 8,
                    paddle.shape.getPosition().y - 16
                );
            }
            else
            {
                b.vel.y = -std::abs(b.vel.y);
                b.shape.move(0, -2);
            }
        }

        for (auto& block : blocks)
        {
            if (!block.alive) continue;

            if (b.shape.getGlobalBounds().intersects(block.shape.getGlobalBounds()))
            {
                resolveCollision(b.shape, b.vel, block.shape.getGlobalBounds());
                b.shape.move(b.vel * 0.1f);

                if (block.type != 1)
                {
                    block.hp--;

                    float t = (float)block.hp / 5.f;

                    block.shape.setFillColor(sf::Color(120 + (1 - t) * 120, 20, 90 + t * 110));

                    score++;

                    if (block.type == 4)
                    {
                        if (block.hp == 2)
                            block.shape.setFillColor(sf::Color(255, 100, 255));
                        else if (block.hp == 1)
                            block.shape.setFillColor(sf::Color(150, 50, 150));
                    }

                    if (block.type == 3)
                        b.vel *= 1.05f;

                    if (block.type == 2 && block.hp <= 0)
                        spawnBonus(block.shape.getPosition().x + 40,
                            block.shape.getPosition().y + 20,
                            rand() % 5 + 1);

                    if (block.hp <= 0)
                        block.alive = false;
                }

                break;
            }
        }
    }

    bonuses.erase(
        std::remove_if(bonuses.begin(), bonuses.end(),
            [](const Bonus& b) { return !b.active; }),
        bonuses.end()
    );

    for (auto& bo : bonuses)
    {
        if (!bo.active) continue;

        bo.update();

        if (bo.getBounds().top > 600)
        {
            bo.active = false;
            continue;
        }

        if (bo.getBounds().intersects(paddle.shape.getGlobalBounds()))
        {
            bo.active = false;

            if (bo.type == 1)
            {
                float w = paddle.shape.getSize().x + 20;
                if (w > 300) w = 300;
                paddle.setSize(w);
            }

            if (bo.type == 2)
                for (auto& b : balls) b.vel *= 1.05f;

            if (bo.type == 3)
            {
                sticky = true;
                stickyTimer = 5.f;
            }

            if (bo.type == 4)
                shield = true;

            if (bo.type == 5)
            {
                balls.push_back(Ball(450, 450));
                balls.back().vel = { 3.f, -3.f };
            }
        }
    }

    bool win = true;
    for (auto& b : blocks)
        if (b.alive && b.type != 1)
            win = false;

    if (win)
        window.close();

    infoText.setString("Lives: " + std::to_string(lives) +
        " Score: " + std::to_string(score));
}

void Game::draw()
{
    window.clear(sf::Color::Black);

    window.draw(paddle.shape);

    for (auto& b : balls)
        window.draw(b.shape);

    for (auto& bl : blocks)
        if (bl.alive)
            window.draw(bl.shape);

    for (auto& bo : bonuses)
        if (bo.active)
            bo.draw(window);

    window.draw(infoText);
    window.display();
}
