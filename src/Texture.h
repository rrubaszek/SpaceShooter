#pragma once

#include <raylib.h>

#include <string>

/// RAII owner of a GPU texture. Move-only: the texture is unloaded exactly once.
class OwnedTexture
{
public:
    OwnedTexture() = default;
    explicit OwnedTexture(const std::string& path);
    ~OwnedTexture();

    OwnedTexture(const OwnedTexture&) = delete;
    OwnedTexture& operator=(const OwnedTexture&) = delete;
    OwnedTexture(OwnedTexture&& other) noexcept;
    OwnedTexture& operator=(OwnedTexture&& other) noexcept;

    [[nodiscard]] const Texture2D& get() const noexcept { return texture_; }
    [[nodiscard]] float width() const noexcept { return static_cast<float>(texture_.width); }
    [[nodiscard]] float height() const noexcept { return static_cast<float>(texture_.height); }

private:
    void release() noexcept;

    Texture2D texture_{};
};

/// All textures used by the game, loaded once at start-up.
struct Assets
{
    OwnedTexture background;
    OwnedTexture player;
    OwnedTexture enemy;
    OwnedTexture laser;

    /// Loads assets from `<directory>/`. Throws std::runtime_error on failure.
    static Assets load(const std::string& directory);
};
