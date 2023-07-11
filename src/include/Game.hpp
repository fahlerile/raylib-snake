#pragma once
#include <raylib.h>

enum GameElement {NOTHING, SNAKE, FOOD};
enum Direction {UP, DOWN, LEFT, RIGHT};

class Game
{
    private:
        int square_size;
        Vector2 offset;

        int length = 1;
        Direction direction;
        Vector2 head_position;
        Vector2 tail_position;

        static const int board_size = 32;
        static const int padding = 0;
        static constexpr const float y_padding_percent = 0.05;  // 5% vertical padding from both sides

        static constexpr const Color color_nothing = BLACK;
        static constexpr const Color color_snake = WHITE;
        static constexpr const Color color_food = RED;

    public:
        GameElement grid[board_size][board_size];
        Game(Vector2 screen_dimensions, Vector2 start_position);
        void render();
        void get_input();
        void update();
};