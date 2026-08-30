#include "WindowManager.h"

WindowManager::WindowManager() { }

void WindowManager::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    auto *app = static_cast<WindowManager *>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS) {
        app->m_keys[key] = true;
    }

    else if (action == GLFW_RELEASE) {
        app->m_keys[key] = false;
    }
}

void WindowManager::ErrorCallback(int error, const char *description)
{
    std::cerr << "Error: " << description << " Code : " << error << std::endl;
};

void WindowManager::WindowResizeCallback(GLFWwindow *window, int width, int height)
{
    auto *app = static_cast<WindowManager *>(glfwGetWindowUserPointer(window));

    glfwGetFramebufferSize(app->m_window->window, (int *) &app->m_window->width, (int *) &app->m_window->height);
    glViewport(0, 0, app->m_window->width, app->m_window->height);
    app->m_updateCamera = true;
}

void WindowManager::SetUpdateCamera(bool updateCamera)
{
    m_updateCamera = updateCamera;
}

Window *WindowManager::CreateWindow(std::string title)
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw. Exiting the application";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, title.data(), NULL, NULL);

    if (!window) {
        std::cerr << "Failed to created glfw window. Exiting the application";
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize glad. Exiting the application";
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetErrorCallback(ErrorCallback);
    glfwSetWindowSizeCallback(window, WindowResizeCallback);
    glfwSwapInterval(1);

    glfwSetWindowUserPointer(window, this);

    m_window = new Window{window, mode->width, mode->height};

    return m_window;
}

glm::vec2 WindowManager::GetResolution()
{
    return glm::vec2(m_window->width, m_window->height);
}