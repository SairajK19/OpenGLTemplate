#pragma once

#include <string>

#include <glad/glad.h>
#include <glfw3.h>

#include "Utils.h"

class Texture
{
private:
    TextureID texture;

public:
    int w, h, channels;

    Texture();
    void LoadTexture(std::string path);
    TextureID GetTexture();
    glm::vec2 GetDimensions();
    void Init();
    void Bind();
    ~Texture();
};