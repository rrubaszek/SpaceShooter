#pragma once

#include <cstddef>

/// Compile-time game tuning. All speeds are expressed in pixels per second
/// so that gameplay is independent of the frame rate.
namespace config
{
    inline constexpr int screenWidth = 1400;
    inline constexpr int screenHeight = 583;
    inline constexpr int targetFps = 60;
    inline constexpr const char* windowTitle = "Space Shooter";
    inline constexpr float maxFrameTime = 1.0f / 20.0f; // seconds

    inline constexpr float playerSpeedX = 600.0f;
    inline constexpr float playerSpeedY = 480.0f;
    inline constexpr std::size_t maxPlayerLasers = 4;

    inline constexpr float enemySpeed = 480.0f;
    inline constexpr std::size_t maxEnemies = 4;
    inline constexpr float enemySpawnInterval = 1.5f;  // seconds
    inline constexpr float enemyShotInterval = 0.5f;   // seconds

    inline constexpr float laserSpeed = 960.0f;

    inline constexpr int pointsPerEnemy = 10;
} // namespace config
