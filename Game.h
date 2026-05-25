#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Bonus.h"

class Game
{
private:
    sf::RenderWindow window;
    Paddle paddle;
    std::vector<Ball> balls;
    std::vector<Block> blocks;
    std::vector<Bonus> bonuses;

    int lives;
    int score;
    bool shield;
    bool sticky;
    float stickyTimer;
    
    sf::Font font;
    sf::Text infoText;

    void spawnBlocks();
    void spawnBonus(float x, float y, int type);
    void resetBall(Ball& b);

public:
    Game();
    void run();
    void update();
    void draw();
};

#endif