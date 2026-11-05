#pragma once

#include <raylib.h>

/// Common state for every object living in the game world.
/// Position is the top-left corner of the sprite.
class Entity
{
public:
    Entity(Vector2 position, const Texture2D& texture) noexcept
        : position_(position), texture_(&texture)
    {
    }
    virtual ~Entity() = default;

    Entity(const Entity&) = default;
    Entity& operator=(const Entity&) = default;
    Entity(Entity&&) = default;
    Entity& operator=(Entity&&) = default;

    virtual void update(float dt) = 0;

    void draw() const { DrawTextureV(*texture_, position_, WHITE); }

    [[nodiscard]] Vector2 position() const noexcept { return position_; }
    [[nodiscard]] Vector2 size() const noexcept
    {
        return {static_cast<float>(texture_->width), static_cast<float>(texture_->height)};
    }
    [[nodiscard]] Rectangle bounds() const noexcept
    {
        const Vector2 s = size();
        return {position_.x, position_.y, s.x, s.y};
    }
    [[nodiscard]] Vector2 center() const noexcept
    {
        const Vector2 s = size();
        return {position_.x + s.x / 2.0f, position_.y + s.y / 2.0f};
    }

    [[nodiscard]] bool collidesWith(const Entity& other) const noexcept
    {
        return CheckCollisionRecs(bounds(), other.bounds());
    }

    /// True when the entity is completely outside the screen.
    [[nodiscard]] bool isOffScreen(float screenWidth, float screenHeight) const noexcept;

protected:
    Vector2 position_;
    const Texture2D* texture_;
};

/// Player-controlled ship (W/A/S/D or arrow keys).
class Player final : public Entity
{
public:
    Player(Vector2 position, const Texture2D& texture) noexcept : Entity(position, texture) {}

    void update(float dt) override;

    /// Point from which the player's lasers are emitted (front of the ship).
    [[nodiscard]] Vector2 gunPosition() const noexcept;
};

/// Enemy ship flying from right to left.
class Enemy final : public Entity
{
public:
    Enemy(Vector2 position, const Texture2D& texture) noexcept : Entity(position, texture) {}

    void update(float dt) override;

    /// Point from which the enemy's lasers are emitted (front of the ship).
    [[nodiscard]] Vector2 gunPosition() const noexcept;
};

/// Laser projectile moving horizontally.
class Laser final : public Entity
{
public:
    enum class Direction { Left = -1, Right = 1 };

    /// Creates a laser whose vertical center and leading edge are placed at `origin`.
    Laser(Vector2 origin, Direction direction, const Texture2D& texture) noexcept;

    void update(float dt) override;

private:
    Direction direction_;
};
