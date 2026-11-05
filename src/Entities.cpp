#include "Entities.h"

#include "Config.h"

#include <algorithm>

bool Entity::isOffScreen(float screenWidth, float screenHeight) const noexcept
{
    const Rectangle b = bounds();
    return b.x + b.width < 0.0f || b.x > screenWidth || b.y + b.height < 0.0f || b.y > screenHeight;
}

void Player::update(float dt)
{
    Vector2 move{0.0f, 0.0f};
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    move.y -= 1.0f;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  move.y += 1.0f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  move.x -= 1.0f;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) move.x += 1.0f;

    position_.x += move.x * config::playerSpeedX * dt;
    position_.y += move.y * config::playerSpeedY * dt;

    // Keep the whole sprite inside the window.
    const Vector2 s = size();
    position_.x = std::clamp(position_.x, 0.0f, static_cast<float>(config::screenWidth) - s.x);
    position_.y = std::clamp(position_.y, 0.0f, static_cast<float>(config::screenHeight) - s.y);
}

Vector2 Player::gunPosition() const noexcept
{
    return {position_.x + size().x, center().y};
}

void Enemy::update(float dt)
{
    position_.x -= config::enemySpeed * dt;
}

Vector2 Enemy::gunPosition() const noexcept
{
    return {position_.x, center().y};
}

Laser::Laser(Vector2 origin, Direction direction, const Texture2D& texture) noexcept
    : Entity(origin, texture), direction_(direction)
{
    const Vector2 s = size();
    position_.y -= s.y / 2.0f;
    if (direction_ == Direction::Left)
    {
        position_.x -= s.x;
    }
}

void Laser::update(float dt)
{
    position_.x += static_cast<float>(direction_) * config::laserSpeed * dt;
}
