#include <raylib.h>
#include "Snake.hpp"
#include "Game.hpp"

#include <iostream>

Game::Game(Vector2 window_dimensions, Vector2 starting_position, Direction direction)
{
    Vector2 speed;
    this->direction = direction;
    this->window_dimensions = window_dimensions;

    if (direction == UP)
        speed = (Vector2) {0.0f, -this->snakepart_size};
    else if (direction == DOWN)
        speed = (Vector2) {0.0f, this->snakepart_size};
    else if (direction == LEFT)
        speed = (Vector2) {-this->snakepart_size, 0.0f};
    else  // if RIGHT
        speed = (Vector2) {this->snakepart_size, 0.0f};

    this->snake.push_back(
        (SnakePart) {
            (Vector2) {this->snakepart_size, this->snakepart_size},
            starting_position,
            speed,
            this->head_color
        }
    );
}

void Game::update()
{
    // input
    Vector2 new_head_speed {0, 0};
    if (IsKeyDown(KEY_UP))
    {
        this->direction = UP;
        new_head_speed = (Vector2) {0.0f, -this->snakepart_size};
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        this->direction = DOWN;
        new_head_speed = (Vector2) {0.0f, this->snakepart_size};
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        this->direction = LEFT;
        new_head_speed = (Vector2) {-this->snakepart_size, 0.0f};
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        this->direction = RIGHT;
        new_head_speed = (Vector2) {this->snakepart_size, 0.0f};
    }
    else
        new_head_speed = this->snake[0].speed;

    if (this->frame_counter % this->frame_num == 0)
    {
        this->snake.insert(this->snake.begin(),
            (SnakePart) {
                (Vector2) {this->snakepart_size, this->snakepart_size},
                (Vector2) {this->snake[0].position.x + this->snake[0].speed.x, this->snake[0].position.y + this->snake[0].speed.y},
                new_head_speed,
                this->head_color
            }
        );
        this->snake.pop_back();

        // if new head is out of bounds
        if (this->snake[0].position.x < 0 || this->snake[0].position.x >= this->window_dimensions.x ||
            this->snake[0].position.y < 0 || this->snake[0].position.y >= this->window_dimensions.y)
        {
            std::cout << "Game Over" << std::endl;
            exit(0);
        }
    }

    this->frame_counter++;
}

void Game::draw()
{
    BeginDrawing();

        ClearBackground(WHITE);

        for (auto part : this->snake)
        {
            DrawRectangleV(part.position, part.size, part.color);
        }

    EndDrawing();
}