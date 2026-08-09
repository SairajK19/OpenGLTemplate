#include <iostream>
#include <stddef.h>

#include "Application.h"
#include "Constants.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

Application::Application() { }

void Application::Start()
{
    std::cout << "Starting OpenGLTemplate!" << std::endl;
    Application::Init();
}

void Application::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    auto *app = static_cast<Application *>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS) {
        app->m_keys[key] = true;
    }

    else if (action == GLFW_RELEASE) {
        app->m_keys[key] = false;
    }
}

void Application::ErrorCallback(int error, const char *description)
{
    std::cerr << "Error: " << description << " Code : " << error << std::endl;
};

void Application::Init()
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw. Exiting the application";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(m_width, m_height, "Breakout", NULL, NULL);

    if (!m_window) {
        std::cerr << "Failed to created glfw window. Exiting the application";
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize glad. Exiting the application";
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(m_window, KeyCallback);
    glfwSetErrorCallback(ErrorCallback);
    glfwSwapInterval(1);

    glfwSetWindowUserPointer(m_window, this);

    ResourceManager::Instance.AddShader("res/shaders/vert.glsl", "res/shaders/frag.glsl", DEFAULT_SHADER, ShaderType::Default);
    ResourceManager::Instance.AddShader("res/shaders/texVert.glsl", "res/shaders/texFrag.glsl", TEXTURE_SHADER, ShaderType::Texture);

    ResourceManager::Instance.AddTexture("res/solaire_of_astora.png", SOLAIRE_OF_ASTORA);

    m_renderer.Init();

    std::cout << "Startup done!" << std::endl;
    Application::Run();
}

void Application::Draw()
{
    float time = glfwGetTime();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight), 0.0f, -1.0f, 1.0f);

    auto defaultShader = ResourceManager::Instance.GetShader(DEFAULT_SHADER);
    defaultShader.SetFloat("time", time);
    defaultShader.SetVec2f("resolution", glm::vec2(m_windowWidth, m_windowHeight));
    defaultShader.SetMat4("projection", projection);

    auto texShader = ResourceManager::Instance.GetShader(TEXTURE_SHADER);
    texShader.SetFloat("time", time);
    texShader.SetMat4("projection", projection);

    Texture solaire = ResourceManager::Instance.GetTexture(SOLAIRE_OF_ASTORA);
    glm::vec2 resolution = glm::vec2(m_windowWidth, m_windowHeight);
    float scale = 1.f;
    glm::vec2 position = (resolution / 2.f) - ((solaire.GetDimensions() * scale) / 2.f);

    defaultShader.Use();
    m_renderer.DrawQuad(glm::vec2(0, 0), resolution);

    texShader.Use();
    m_renderer.Begin();

    m_renderer.DrawSprite(solaire, position, solaire.GetDimensions() * scale, glm::vec4(0, 0, 1, 1), glm::vec4(1, 1, 1, 1), 0.0f);

    m_renderer.End();
}

void Application::ProcessInput(float &dt)
{
    if (m_keys[GLFW_KEY_ESCAPE]) {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    }
}

void Application::Update(float &dt)
{
}

void Application::ProcessKeyTimeout(float &dt)
{
    float currentTimeout = m_keyTimeout[GLFW_KEY_SPACE];
    float newTimeout = std::fmax(0.0f, currentTimeout - dt * 100);
    m_keyTimeout[GLFW_KEY_SPACE] = newTimeout;
}

void Application::Run()
{
    float dt = 0.0f;
    float lastFrame = glfwGetTime();
    int fps = 0;
    float timeElapsed = 0;
    while (!glfwWindowShouldClose(m_window)) {
        glfwGetFramebufferSize(m_window, (int *) &m_windowWidth, (int *) &m_windowHeight);
        glViewport(0, 0, m_windowWidth, m_windowHeight);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        dt = glfwGetTime() - lastFrame;
        lastFrame = glfwGetTime();

        fps++;
        timeElapsed += dt;

        if (timeElapsed >= 1.0) {
            std::cout << "FPS: " << fps << std::endl;
            fps = 0;
            timeElapsed = 0;
        }

        ProcessKeyTimeout(dt);
        ProcessInput(dt);

        Update(dt);

        Draw();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

Application::~Application()
{
    std::cout << "Closing the Application" << std::endl;
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
