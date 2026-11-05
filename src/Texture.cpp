#include "Texture.h"

#include <stdexcept>
#include <utility>

OwnedTexture::OwnedTexture(const std::string& path)
    : texture_(LoadTexture(path.c_str()))
{
    if (!IsTextureValid(texture_))
    {
        throw std::runtime_error("Failed to load texture: " + path);
    }
}

OwnedTexture::~OwnedTexture()
{
    release();
}

OwnedTexture::OwnedTexture(OwnedTexture&& other) noexcept
    : texture_(std::exchange(other.texture_, Texture2D{}))
{
}

OwnedTexture& OwnedTexture::operator=(OwnedTexture&& other) noexcept
{
    if (this != &other)
    {
        release();
        texture_ = std::exchange(other.texture_, Texture2D{});
    }
    return *this;
}

void OwnedTexture::release() noexcept
{
    if (texture_.id != 0)
    {
        UnloadTexture(texture_);
        texture_ = Texture2D{};
    }
}

Assets Assets::load(const std::string& directory)
{
    const std::string base = directory.empty() || directory.back() == '/' ? directory : directory + '/';

    Assets assets;
    assets.background = OwnedTexture(base + "MainBG_zloty.png");
    assets.player = OwnedTexture(base + "player2.png");
    assets.enemy = OwnedTexture(base + "enemy.png");
    assets.laser = OwnedTexture(base + "shoot1.png");
    return assets;
}
