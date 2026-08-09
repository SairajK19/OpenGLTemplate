#pragma once

#include "glm.hpp"
#include <cfloat>

struct Position
{
    float x;
    float y;
    float z;
};

struct Color
{
    float r, g, b, a;
};

struct TexCoord
{
    float u, v;
};

struct ColorVertex
{
    Position pos;
    Color color;
};

struct TextureVertex
{
    Position pos;
    Color color;
    TexCoord uv;
};

enum Direction { UP, DOWN, LEFT, RIGHT };

typedef unsigned int TextureID;
typedef std::tuple<bool, Direction, glm::vec2> Collision;

static inline Direction GetNormVectorDirection(glm::vec2 v1)
{
    glm::vec2 cardinalDirs[4] = {
        glm::vec2(0, 1),  // UP
        glm::vec2(0, -1), // DOWN
        glm::vec2(-1, 0), // LEFT
        glm::vec2(1, 0)   // RIGHT
    };

    // If a vector points in a direction then the dot product between them is one. ie. the angle is zero
    float max = -FLT_MAX;
    int best = -1;
    for (int i = 0; i < 4; i++) {
        float dot = glm::dot(v1, cardinalDirs[i]);

        if (dot > max) {
            max = dot;
            best = i;
        }
    }

    return (Direction) best;
}