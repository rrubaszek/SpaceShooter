#include "Config.h"
#include "Game.h"
#include "Texture.h"

#include <raylib.h>

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

namespace
{
    /// RAII guard for the raylib window / OpenGL context.
    class Window
    {
    public:
        Window(int width, int height, const char* title)
        {
            InitWindow(width, height, title);
            SetTargetFPS(config::targetFps);
        }
        ~Window() { CloseWindow(); }

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;
    };

    /// Assets are looked up next to the executable first, then in the working directory.
    std::string findAssetDirectory()
    {
        const std::string besideExe = std::string(GetApplicationDirectory()) + "assets";
        if (DirectoryExists(besideExe.c_str()))
        {
            return besideExe;
        }
        return "assets";
    }
} // namespace

int main()
{
    try
    {
        Window window(config::screenWidth, config::screenHeight, config::windowTitle);
        SetExitKey(KEY_ESCAPE);

        const Assets assets = Assets::load(findAssetDirectory());
        Game game(assets);
        game.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Fatal error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
