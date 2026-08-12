#pragma once

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "WindowManager.h"

#include <glad/glad.h>
#include <glfw3.h>

class Application
{
private:
    // Window
    WindowManager m_windowManager;
    Window *m_window = nullptr;
    unsigned int m_width = 640 * 1.5, m_height = 480 * 1.5;
    unsigned int m_windowWidth, m_windowHeight;

    // Renderer
    SpriteRenderer m_renderer;

    // GameObjects
    GameObject m_player;
    const glm::vec2 m_playerInitialVel = glm::vec2(500.0f);
    const glm::vec2 m_ballInitialVel = glm::vec2(100.0f, -350.0f);
    float m_ballRadius = 12.5f;

    // Input
    std::unordered_map<int, float> m_keyTimeout;

    void Run();
    void Init();
    void Update(float &dt);
    void Draw();
    void ProcessInput(float &dt);
    void PerformCollisionDetection();
    void InitLevel();
    GLFWwindow *CreateWindow();

    void ProcessKeyTimeout(float &dt);
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void ErrorCallback(int error, const char *description);

public:
    Application();

    void Start();

    ~Application();
};
