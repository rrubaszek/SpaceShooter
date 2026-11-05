#pragma once

#include "Entities.h"
#include "Texture.h"

#include <random>
#include <vector>

/// Owns the whole game state and runs the update / draw cycle.
class Game
{
public:
    explicit Game(const Assets& assets);

    /// Runs the main loop until the window is closed.
    void run();

private:
    enum class State { Playing, Paused, GameOver };

    void reset();

    void update(float dt);
    void updatePlaying(float dt);
    void spawnEnemies(float dt);
    void enemiesShoot(float dt);
    void handleCollisions();
    void removeDeadEntities();

    void draw() const;
    void drawHud() const;
    static void drawCenteredText(const char* text, int y, int fontSize, Color color);

    const Assets& assets_;
    std::mt19937 rng_;

    State state_ = State::Playing;
    Player player_;
    std::vector<Enemy> enemies_;
    std::vector<Laser> playerLasers_;
    std::vector<Laser> enemyLasers_;

    float enemySpawnTimer_ = 0.0f;
    float enemyShotTimer_ = 0.0f;
    int score_ = 0;
    int highScore_ = 0;
};
