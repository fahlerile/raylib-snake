#include <raylib.h>
#include "Game.hpp"

int main(void)
{
    const Vector2 window_dimensions {800, 600};

    InitWindow(window_dimensions.x, window_dimensions.y, "Snake!");
    SetTargetFPS(60);

    Game game(window_dimensions);

    while (!WindowShouldClose())
    {
        game.update();
        game.draw();
    }

    CloseWindow();
    return 0;
}