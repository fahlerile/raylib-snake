#include <raylib.h>
#include "Game.hpp"

int main(void)
{
    const Vector2 window_dimensions {800, 600};

    InitWindow(window_dimensions.x, window_dimensions.y, "Snake!");
    SetTargetFPS(60);

    Game game(window_dimensions, (Vector2) {100, 100}, RIGHT);

    while (!WindowShouldClose())
    {
        game.update();
        game.draw();
    }

    CloseWindow();
    return 0;
}