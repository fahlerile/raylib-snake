#include <raylib.h>
#include "Game.hpp"

int main(void)
{
    const Vector2 screen_dimensions {800, 600};

    Game game(screen_dimensions, (Vector2) {20, 20});

    InitWindow(screen_dimensions.x, screen_dimensions.y, "Snake!");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(WHITE);

            game.get_input();
            game.update();

            game.render();

        EndDrawing();

        WaitTime(0.5f);
    }

    CloseWindow();
    return 0;
}