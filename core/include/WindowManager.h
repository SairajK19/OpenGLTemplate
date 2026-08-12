#pragma once

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
public:
    std::unordered_map<int, bool> m_keys;
    WindowManager();
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void ErrorCallback(int error, const char *description);
    Window *CreateWindow(std::string title);
};
