#include "GameObject.h"

#include "ResourceManager.h"

GameObject::GameObject() { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, std::string textureName, glm::vec4 color, float rotation)
    : m_pos(pos)
    , m_size(size)
    , m_velocity(velocity)
    , m_color(color)
    , m_textureName(textureName)
    , m_rotation(rotation)
{ }

void GameObject::Draw(SpriteRenderer &renderer)
{
    Texture tex = ResourceManager::Instance.GetTexture(m_textureName);

    // TODO: Think of creating a sprite sheet manager. 4th argument is the sprite sheet sprite coordinate
    renderer.DrawSprite(tex, m_pos, m_size, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_color, m_rotation);
}

void GameObject::SetDestroyed(bool destroyed)
{
    m_destroyed = destroyed;
}

void GameObject::SetPosition(glm::vec2 pos)
{
    m_pos = pos;
}

glm::vec2 GameObject::GetPosition()
{
    return m_pos;
}

glm::vec2 GameObject::GetSize()
{
    return m_size;
}

std::string GameObject::GetTextureName()
{
    return m_textureName;
}

bool GameObject::IsDestroyed()
{
    return m_destroyed;
}

GameObject::~GameObject() { }