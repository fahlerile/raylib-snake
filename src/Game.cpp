#include <raylib.h>
#include "SnakeAndFood.hpp"
#include "Game.hpp"

#include <iostream>

Game::Game(Vector2 window_dimensions)
{
    Vector2 speed;
    this->window_dimensions = window_dimensions;

    this->direction = (Direction) GetRandomValue(0, 3);  // randomly initializing direction
    Vector2 starting_position {  // randomly initializing starting position
        (float) GetRandomValue(window_dimensions.x * 0.3 / this->snakepart_size, window_dimensions.x * 0.7 / this->snakepart_size) * this->snakepart_size,
        (float) GetRandomValue(window_dimensions.y * 0.3 / this->snakepart_size, window_dimensions.y * 0.7 / this->snakepart_size) * this->snakepart_size
    };

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

    this->food = (Food) {
        (Vector2) {this->snakepart_size, this->snakepart_size},
        (Vector2) {
            (float) GetRandomValue(0, window_dimensions.x / this->snakepart_size) * this->snakepart_size,
            (float) GetRandomValue(0, window_dimensions.y / this->snakepart_size) * this->snakepart_size
        },
        this->food_color
    };
}

void Game::update()
{
    if (!this->game_over)
    {
        if (this->paused)
        {
            if (IsKeyDown(KEY_P))
                this->paused = false;
        }

        else  // if not paused
        {
            // input handling
            Vector2 new_head_speed {0, 0};
            if (IsKeyDown(KEY_UP) && this->direction != DOWN)
            {
                this->direction = UP;
                new_head_speed = (Vector2) {0.0f, -this->snakepart_size};
            }
            else if (IsKeyDown(KEY_DOWN) && this->direction != UP)
            {
                this->direction = DOWN;
                new_head_speed = (Vector2) {0.0f, this->snakepart_size};
            }
            else if (IsKeyDown(KEY_LEFT) && this->direction != RIGHT)
            {
                this->direction = LEFT;
                new_head_speed = (Vector2) {-this->snakepart_size, 0.0f};
            }
            else if (IsKeyDown(KEY_RIGHT) && this->direction != LEFT)
            {
                this->direction = RIGHT;
                new_head_speed = (Vector2) {this->snakepart_size, 0.0f};
            }
            else if (IsKeyDown(KEY_P))
            {
                this->paused = true;
                return;
            }
            else
                new_head_speed = this->snake[0].speed;

            if (this->frame_counter % this->frame_num == 0)  // every `frame_num` frames
            {
                this->snake.insert(this->snake.begin(),  // create a new head for the snake
                    (SnakePart) {
                        (Vector2) {this->snakepart_size, this->snakepart_size},
                        (Vector2) {this->snake[0].position.x + this->snake[0].speed.x, this->snake[0].position.y + this->snake[0].speed.y},
                        new_head_speed,
                        this->body_color
                    }
                );
                this->snake[1].color = this->body_color;
                this->snake.pop_back();  // delete the tail

                // if new head is out of bounds, set game_over to true
                if (this->snake[0].position.x < 0 || this->snake[0].position.x >= this->window_dimensions.x ||
                    this->snake[0].position.y < 0 || this->snake[0].position.y >= this->window_dimensions.y)
                {
                    this->game_over = true;
                }

                // if new head is in the food
                if (this->snake[0].position.x == this->food.position.x &&
                    this->snake[0].position.y == this->food.position.y)
                {
                    this->snake.insert(this->snake.begin(),  // create a new snakepart
                        (SnakePart) {
                            (Vector2) {this->snakepart_size, this->snakepart_size},
                            (Vector2) {this->snake[0].position.x, this->snake[0].position.y},
                            new_head_speed,
                            this->body_color
                        }
                    );

                    this->food = (Food) {  // replace the food
                        (Vector2) {this->snakepart_size, this->snakepart_size},
                        (Vector2) {
                            (float) GetRandomValue(0, window_dimensions.x / this->snakepart_size) * this->snakepart_size,
                            (float) GetRandomValue(0, window_dimensions.y / this->snakepart_size) * this->snakepart_size
                        },
                        this->food_color
                    };
                }

                else  // need this because i create new part in the head basically
                {
                    // if new head has the same coords as some of the snakeparts
                    int n_parts = this->snake.size();
                    for (int i = 1; i < n_parts; i++)
                    {
                        if (this->snake[i].position.x == this->snake[0].position.x &&
                            this->snake[i].position.y == this->snake[0].position.y)
                        {
                            this->game_over = true;
                        }
                    }
                }
            }

            this->frame_counter++;
        }
    }
    else  // if game over
    {
        if (IsKeyDown(KEY_ENTER))
        {
            this->game_over = false;
            this->snake.clear();

            Vector2 speed;
            this->direction = (Direction) GetRandomValue(0, 3);  // randomly initializing direction
            Vector2 starting_position {  // randomly initializing starting position
                (float) GetRandomValue(window_dimensions.x * 0.3 / this->snakepart_size, window_dimensions.x * 0.7 / this->snakepart_size) * this->snakepart_size,
                (float) GetRandomValue(window_dimensions.y * 0.3 / this->snakepart_size, window_dimensions.y * 0.7 / this->snakepart_size) * this->snakepart_size
            };

            if (this->direction == UP)
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

            this->food = (Food) {  // replace the food
                (Vector2) {this->snakepart_size, this->snakepart_size},
                (Vector2) {
                    (float) GetRandomValue(0, window_dimensions.x / this->snakepart_size) * this->snakepart_size,
                    (float) GetRandomValue(0, window_dimensions.y / this->snakepart_size) * this->snakepart_size
                },
                this->food_color
            };
        }
    }
}

void Game::draw()
{
    BeginDrawing();

        ClearBackground(WHITE);

        if (!this->game_over)
        {
            if (this->paused)
            {
                DrawText("Game is paused. Press [P] to continue", 10, 10, 30, BLACK);
            }

            DrawRectangleV(this->food.position, this->food.size, this->food.color);
            for (auto part : this->snake)
            {
                DrawRectangleV(part.position, part.size, part.color);
            }
        }
        else  // game over
        {
            DrawText("Game Over! Press [ENTER] to restart!", 10, 10, 30, BLACK);
        }

    EndDrawing();
}