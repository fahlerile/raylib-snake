#pragma once
#include <raylib.h>

struct SnakePart
{
    Vector2 size;
    Vector2 position;
    Vector2 speed;
    Color color;
};

struct Food
{
    Vector2 size;
    Vector2 position;
    Color color;
};