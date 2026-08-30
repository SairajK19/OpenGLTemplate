#include "Camera2D.h"

Camera2D::Camera2D(glm::vec2 center, glm::vec2 size, glm::vec2 velocity)
{
    m_pos = center - (size / 2.0f);
    m_size = size;
    m_velocity = velocity;
    m_view = glm::mat4(1.0f);
    m_proj = glm::ortho(0.0f, m_size.x, m_size.y, 0.0f, -1.0f, 1.0f);
    m_center = center;
    SetView();
}

void Camera2D::Move(float &dt, WindowManager &windowManager)
{
    glm::vec2 vel = m_velocity * dt;
    if (windowManager.m_keys[GLFW_KEY_W]) {
        m_pos.y -= vel.y;
    } else if (windowManager.m_keys[GLFW_KEY_A]) {
        m_pos.x -= vel.x;
    } else if (windowManager.m_keys[GLFW_KEY_S]) {
        m_pos.y += vel.y;
    } else if (windowManager.m_keys[GLFW_KEY_D]) {
        m_pos.x += vel.x;
    }
}

void Camera2D::SetSize(glm::vec2 size)
{
    m_size = size;
    SetCenter(size / 2.f);
    SetProjection();
    SetView();
}

void Camera2D::SetCenter(glm::vec2 center)
{
    m_center = center;
    m_pos = m_center - (m_size / 2.0f);
    SetProjection();
    SetView();
}

void Camera2D::SetView()
{
    m_view = glm::mat4(1.0f);
    m_view = glm::translate(m_view, glm::vec3(-m_pos.x, -m_pos.y, 0));
}

void Camera2D::SetProjection()
{
    m_proj = glm::ortho(0.0f, m_size.x, m_size.y, 0.0f, -1.0f, 1.0f);
}

glm::mat4 Camera2D::GetView()
{
    return m_view;
}

glm::mat4 Camera2D::GetProjection()
{
    return m_proj;
}

Camera2D::~Camera2D() { }