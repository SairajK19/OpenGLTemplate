#pragma once

#include "glm.hpp"
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <unordered_map>

struct Window
{
    GLFWwindow *window;
    int width;
    int height;
};

class WindowManager
{
private:
    Window *m_window;

public:
    std::unordered_map<int, bool> m_keys;
    bool m_updateCamera;
    WindowManager();
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void ErrorCallback(int error, const char *description);
    static void WindowResizeCallback(GLFWwindow *window, int width, int height);
    Window *CreateWindow(std::string title);
    void SetUpdateCamera(bool updateCamera);
    glm::vec2 GetResolution();
};
