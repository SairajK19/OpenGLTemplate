#include <iostream>
#include <stddef.h>

#include "Application.h"
#include "Constants.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "WindowManager.h"

Application::Application() { }

void Application::Start()
{
    std::cout << "Starting OpenGLTemplate!" << std::endl;
    Application::Init();
}

void Application::Init()
{
    m_windowManager = WindowManager();
    m_window = m_windowManager.CreateWindow("Evolution");

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
    if (m_windowManager.m_keys[GLFW_KEY_ESCAPE]) {
        glfwSetWindowShouldClose(m_window->window, GLFW_TRUE);
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
    while (!glfwWindowShouldClose(m_window->window)) {
        glfwGetFramebufferSize(m_window->window, (int *) &m_windowWidth, (int *) &m_windowHeight);
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

        glfwSwapBuffers(m_window->window);
        glfwPollEvents();
    }
}

Application::~Application()
{
    std::cout << "Closing the Application" << std::endl;
    glfwDestroyWindow(m_window->window);
    glfwTerminate();
}
