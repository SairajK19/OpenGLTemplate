#pragma once

#include "SpriteRenderer.h"

class GameObject
{
protected:
    glm::vec2 m_pos, m_size, m_velocity;
    glm::vec4 m_color;
    std::string m_textureName;
    bool m_destroyed = false;

public:
    float m_rotation;

    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, std::string textureName, glm::vec4 color, float rotation = 0.0f);

    void SetPosition(glm::vec2 pos);
    void SetDestroyed(bool destroyed);

    void Draw(SpriteRenderer &renderer);

    glm::vec2 GetPosition();
    glm::vec2 GetSize();
    std::string GetTextureName();

    bool IsDestroyed();

    ~GameObject();
};