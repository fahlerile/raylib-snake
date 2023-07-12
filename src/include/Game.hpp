#pragma once
#include <vector>
#include "SnakeAndFood.hpp"

enum Direction {UP, DOWN, LEFT, RIGHT};

class Game
{
    private:
        static const constexpr Color head_color = DARKBLUE;
        static const constexpr Color body_color = BLUE;
        static const constexpr Color food_color = RED;
        static const int snakepart_size = 25;

        Vector2 window_dimensions;
        int frame_num = 10; // per how many frames the snake is going to "walk"

        std::vector<SnakePart> snake;
        Food food;

        Direction direction;
        bool game_over = false;
        bool paused = false;
        int frame_counter = 0;

    public:
        Game(Vector2 window_dimensions);
        void update();
        void draw();
};