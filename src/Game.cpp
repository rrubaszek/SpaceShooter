#include "Game.h"

#include "Config.h"

#include <algorithm>
#include <string>

namespace
{
    constexpr auto screenW = static_cast<float>(config::screenWidth);
    constexpr auto screenH = static_cast<float>(config::screenHeight);

    Vector2 playerStartPosition(const Texture2D& texture)
    {
        return {screenW / 10.0f, (screenH - static_cast<float>(texture.height)) / 2.0f};
    }

    /// Removes every element for which `pred` is true (erase-remove idiom).
    template <typename Container, typename Pred>
    void eraseIf(Container& c, Pred pred)
    {
        c.erase(std::remove_if(c.begin(), c.end(), pred), c.end());
    }
} // namespace

Game::Game(const Assets& assets)
    : assets_(assets),
      rng_(std::random_device{}()),
      player_(playerStartPosition(assets.player.get()), assets.player.get())
{
    reset();
}

void Game::reset()
{
    state_ = State::Playing;
    player_ = Player(playerStartPosition(assets_.player.get()), assets_.player.get());
    enemies_.clear();
    playerLasers_.clear();
    enemyLasers_.clear();
    enemySpawnTimer_ = 0.0f;
    enemyShotTimer_ = 0.0f;
    score_ = 0;
}

void Game::run()
{
    while (!WindowShouldClose())
    {
        // Clamp the time step so a long stall (window drag, loading) cannot
        // teleport entities through each other.
        update(std::min(GetFrameTime(), config::maxFrameTime));
        draw();
    }
}

void Game::update(float dt)
{
    switch (state_)
    {
    case State::Playing:
        if (IsKeyPressed(KEY_P))
        {
            state_ = State::Paused;
            return;
        }
        updatePlaying(dt);
        break;
    case State::Paused:
        if (IsKeyPressed(KEY_P))
        {
            state_ = State::Playing;
        }
        break;
    case State::GameOver:
        if (IsKeyPressed(KEY_ENTER))
        {
            reset();
        }
        break;
    }
}

void Game::updatePlaying(float dt)
{
    player_.update(dt);

    if (IsKeyPressed(KEY_SPACE) && playerLasers_.size() < config::maxPlayerLasers)
    {
        playerLasers_.emplace_back(player_.gunPosition(), Laser::Direction::Right, assets_.laser.get());
    }

    spawnEnemies(dt);
    enemiesShoot(dt);

    for (auto& enemy : enemies_) enemy.update(dt);
    for (auto& laser : playerLasers_) laser.update(dt);
    for (auto& laser : enemyLasers_) laser.update(dt);

    handleCollisions();
    removeDeadEntities();

    highScore_ = std::max(highScore_, score_);
}

void Game::spawnEnemies(float dt)
{
    enemySpawnTimer_ += dt;
    if (enemySpawnTimer_ < config::enemySpawnInterval)
    {
        return;
    }
    enemySpawnTimer_ -= config::enemySpawnInterval;

    if (enemies_.size() >= config::maxEnemies)
    {
        return;
    }

    const float maxY = screenH - assets_.enemy.height();
    std::uniform_real_distribution<float> distY(0.0f, maxY);
    enemies_.emplace_back(Vector2{screenW, distY(rng_)}, assets_.enemy.get());
}

void Game::enemiesShoot(float dt)
{
    enemyShotTimer_ += dt;
    if (enemyShotTimer_ < config::enemyShotInterval)
    {
        return;
    }
    enemyShotTimer_ -= config::enemyShotInterval;

    // Only enemies that are actually visible may shoot.
    std::vector<const Enemy*> shooters;
    for (const auto& enemy : enemies_)
    {
        if (enemy.position().x < screenW)
        {
            shooters.push_back(&enemy);
        }
    }
    if (shooters.empty())
    {
        return;
    }

    std::uniform_int_distribution<std::size_t> pick(0, shooters.size() - 1);
    const Enemy* shooter = shooters[pick(rng_)];
    enemyLasers_.emplace_back(shooter->gunPosition(), Laser::Direction::Left, assets_.laser.get());
}

void Game::handleCollisions()
{
    // Player lasers vs enemies: each laser destroys at most one enemy.
    std::vector<bool> enemyHit(enemies_.size(), false);
    eraseIf(playerLasers_, [&](const Laser& laser) {
        for (std::size_t i = 0; i < enemies_.size(); ++i)
        {
            if (!enemyHit[i] && laser.collidesWith(enemies_[i]))
            {
                enemyHit[i] = true;
                score_ += config::pointsPerEnemy;
                return true;
            }
        }
        return false;
    });

    std::size_t index = 0;
    eraseIf(enemies_, [&](const Enemy&) { return enemyHit[index++]; });

    // Enemies or enemy lasers vs player.
    const auto hitsPlayer = [this](const Entity& e) { return e.collidesWith(player_); };
    if (std::any_of(enemies_.begin(), enemies_.end(), hitsPlayer) ||
        std::any_of(enemyLasers_.begin(), enemyLasers_.end(), hitsPlayer))
    {
        state_ = State::GameOver;
    }
}

void Game::removeDeadEntities()
{
    const auto offScreen = [](const Entity& e) { return e.isOffScreen(screenW, screenH); };
    eraseIf(enemies_, offScreen);
    eraseIf(playerLasers_, offScreen);
    eraseIf(enemyLasers_, offScreen);
}

void Game::draw() const
{
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));
    DrawTexture(assets_.background.get(), 0, 0, WHITE);

    for (const auto& enemy : enemies_) enemy.draw();
    for (const auto& laser : enemyLasers_) laser.draw();
    for (const auto& laser : playerLasers_) laser.draw();
    player_.draw();

    drawHud();

    if (state_ == State::Paused)
    {
        drawCenteredText("PAUSED", config::screenHeight / 2 - 30, 60, RAYWHITE);
        drawCenteredText("Press P to resume", config::screenHeight / 2 + 40, 24, LIGHTGRAY);
    }
    else if (state_ == State::GameOver)
    {
        DrawRectangle(0, 0, config::screenWidth, config::screenHeight, Fade(BLACK, 0.5f));
        drawCenteredText("GAME OVER", config::screenHeight / 2 - 60, 60, RED);
        drawCenteredText(TextFormat("Score: %d", score_), config::screenHeight / 2 + 10, 30, RAYWHITE);
        drawCenteredText("Press ENTER to play again or ESC to quit", config::screenHeight / 2 + 60, 24,
                         LIGHTGRAY);
    }

    EndDrawing();
}

void Game::drawHud() const
{
    DrawFPS(10, 10);
    const char* scoreText = TextFormat("Score: %d   Best: %d", score_, highScore_);
    DrawText(scoreText, config::screenWidth - MeasureText(scoreText, 24) - 10, 10, 24, RAYWHITE);
}

void Game::drawCenteredText(const char* text, int y, int fontSize, Color color)
{
    DrawText(text, (config::screenWidth - MeasureText(text, fontSize)) / 2, y, fontSize, color);
}
