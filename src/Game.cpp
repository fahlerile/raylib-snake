#include <raylib.h>
#include "Game.hpp"

#include <iostream>

Game::Game(Vector2 screen_dimensions, Vector2 start_position)
{
    // calculate square size so that there is padding from borders
    this->square_size = screen_dimensions.y * (1 - 2 * this->y_padding_percent) / this->board_size;

    this->offset.x = (screen_dimensions.x - this->board_size * this->square_size) / 2;
    this->offset.y = screen_dimensions.y * this->y_padding_percent;

    for (int i = 0; i < this->board_size; i++)
    {
        for (int j = 0; j < this->board_size; j++)
        {
            this->grid[i][j] = NOTHING;
        }
    }

    this->direction = (Direction) GetRandomValue(0, 3);
    this->head_position = start_position;
    this->tail_position = start_position;
}

void Game::render()
{
    for (int y = 0; y < this->board_size; y++)
    {
        for (int x = 0; x < this->board_size; x++)
        {
            if (this->grid[y][x] == NOTHING)
                DrawRectangle((this->square_size + this->padding) * x + this->offset.x,
                              (this->square_size + this->padding) * y + this->offset.y,
                              this->square_size, this->square_size, this->color_nothing);

            else if (this->grid[y][x] == SNAKE)
                DrawRectangle((this->square_size + this->padding) * x + this->offset.x,
                              (this->square_size + this->padding) * y + this->offset.y,
                              this->square_size, this->square_size, this->color_snake);

            else
                DrawRectangle((this->square_size + this->padding) * x + this->offset.x,
                              (this->square_size + this->padding) * y + this->offset.y,
                              this->square_size, this->square_size, this->color_food);
        }
    }
}

void Game::get_input()
{
    if (IsKeyPressed(KEY_UP) && this->direction != DOWN)
        this->direction = UP;
    else if (IsKeyDown(KEY_DOWN) && this->direction != UP)
        this->direction = DOWN;
    if (IsKeyDown(KEY_LEFT) && this->direction != RIGHT)
        this->direction = LEFT;
    if (IsKeyDown(KEY_RIGHT) && this->direction != LEFT)
        this->direction = RIGHT;
}

void Game::update()
{
    if (this->direction == UP)
    {
        this->head_position = (Vector2) {this->head_position.x, this->head_position.y - 1};
        this->grid[(int) this->head_position.y][(int) this->head_position.x] = SNAKE;

        this->grid[(int) this->tail_position.y][(int) this->tail_position.x] = NOTHING;
        this->tail_position = (Vector2) {this->tail_position.x, this->tail_position.y - 1};
    }
    else if (this->direction == DOWN)
    {
        this->head_position = (Vector2) {this->head_position.x, this->head_position.y + 1};
        this->grid[(int) this->head_position.y][(int) this->head_position.x] = SNAKE;

        this->grid[(int) this->tail_position.y][(int) this->tail_position.x] = NOTHING;
        this->tail_position = (Vector2) {this->tail_position.x, this->tail_position.y + 1};
    }
    else if (this->direction == LEFT)
    {
        this->head_position = (Vector2) {this->head_position.x - 1, this->head_position.y};
        this->grid[(int) this->head_position.y][(int) this->head_position.x] = SNAKE;

        this->grid[(int) this->tail_position.y][(int) this->tail_position.x] = NOTHING;
        this->tail_position = (Vector2) {this->tail_position.x - 1, this->tail_position.y};
    }
    else
    {
        this->head_position = (Vector2) {this->head_position.x + 1, this->head_position.y};
        this->grid[(int) this->head_position.y][(int) this->head_position.x] = SNAKE;

        this->grid[(int) this->tail_position.y][(int) this->tail_position.x] = NOTHING;
        this->tail_position = (Vector2) {this->tail_position.x + 1, this->tail_position.y};
    }
}
