#pragma once

#include "GameObject.h"
#include "WindowManager.h"

class Camera2D : public GameObject
{
private:
    glm::mat4 m_view, m_proj;
    glm::vec2 m_center, m_zoom;

public:
    Camera2D() { };
    Camera2D(glm::vec2 center, glm::vec2 size, glm::vec2 velocity);

    void Move(float &dt, WindowManager &windowManager);
    void SetSize(glm::vec2 size);
    void SetView();
    void SetCenter(glm::vec2 center);
    void SetProjection();

    glm::mat4 GetView();
    glm::mat4 GetProjection();

    ~Camera2D();
};
