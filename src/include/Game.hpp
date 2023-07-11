#pragma once
#include <vector>
#include "Snake.hpp"

enum Direction {UP, DOWN, LEFT, RIGHT};

class Game
{
    private:
        static const constexpr Color head_color = DARKBLUE;
        static const int snakepart_size = 25;

        int frame_counter = 0;
        std::vector<SnakePart> snake;
        Direction direction;

        int frame_num = 10; // per how many frames the snake is going to "walk"
        Vector2 window_dimensions;

    public:
        Game(Vector2 window_dimensions, Vector2 starting_position, Direction direction);
        void update();
        void draw();
};