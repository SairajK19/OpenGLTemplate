#pragma once

#include "QuadMesh.h"
#include "Texture.hpp"
#include "TextureMesh.h"

class SpriteRenderer
{
private:
    TextureMesh textureMesh;
    QuadMesh quadMesh;
    unsigned int currentTexture;

public:
    SpriteRenderer();
    void Init();
    void DrawQuad(glm::vec2 pos, glm::vec2 dimensions);
    void DrawSprite(Texture &texture, glm::vec2 pos, glm::vec2 dimensions, glm::vec4 texCoord, glm::vec4 color, float angle);
    void Begin();
    void End();
    unsigned int GetInstanceCount();
    ~SpriteRenderer();
};
