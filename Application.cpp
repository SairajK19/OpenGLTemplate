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
    m_window = m_windowManager.CreateWindow("OpenGLTemplate");

    ResourceManager::Instance.AddShader("res/shaders/vert.glsl", "res/shaders/frag.glsl", DEFAULT_SHADER, ShaderType::Default);
    ResourceManager::Instance.AddShader("res/shaders/texVert.glsl", "res/shaders/texFrag.glsl", TEXTURE_SHADER, ShaderType::Texture);

    ResourceManager::Instance.AddTexture("res/solaire_of_astora.png", SOLAIRE_OF_ASTORA);

    glm::vec2 windowRes = m_windowManager.GetResolution();

    m_camera = Camera2D(windowRes / 2.0f, windowRes, glm::vec2(500.0f));

    m_renderer.Init();

    std::cout << "Startup done!" << std::endl;
    Application::Run();
}

void Application::Draw()
{
    float time = glfwGetTime();
    glm::mat4 projection = m_camera.GetProjection();
    glm::mat4 view = m_camera.GetView();

    auto defaultShader = ResourceManager::Instance.GetShader(DEFAULT_SHADER);
    defaultShader.SetFloat("time", time);
    defaultShader.SetVec2f("resolution", glm::vec2(m_windowWidth, m_windowHeight));
    defaultShader.SetMat4("projection", projection);
    defaultShader.SetMat4("view", view);

    auto texShader = ResourceManager::Instance.GetShader(TEXTURE_SHADER);
    texShader.SetFloat("time", time);
    texShader.SetMat4("projection", projection);
    texShader.SetMat4("view", view);

    Texture solaire = ResourceManager::Instance.GetTexture(SOLAIRE_OF_ASTORA);

    defaultShader.Use();
    m_renderer.DrawQuad(glm::vec2(0, 0), m_windowManager.GetResolution());

    texShader.Use();
    m_renderer.Begin();

    Sprite sprite;
    SpriteCoord sc;
    sc.topLeft = glm::vec2(0, 0);
    sc.bottomRight = glm::vec2(1, 1);
    sprite.coord = sc;
    sprite.w = solaire.w;
    sprite.h = solaire.h;

    glm::vec2 resolution = glm::vec2(m_windowWidth, m_windowHeight);
    glm::vec2 position = (resolution / 2.f) - ((solaire.GetDimensions() * 1.0f) / 2.f);
    m_renderer.DrawSprite(solaire, position, sprite, 1.f, glm::vec4(1, 1, 1, 1), 0.0f);

    m_renderer.End();
}

void Application::ProcessInput(float &dt)
{
    if (m_windowManager.m_keys[GLFW_KEY_ESCAPE]) {
        glfwSetWindowShouldClose(m_window->window, GLFW_TRUE);
    } else if (m_windowManager.m_keys[GLFW_KEY_SPACE]) {
        m_camera.SetCenter((m_windowManager.GetResolution() / 2.0f));
    }
}

void Application::Update(float &dt)
{
    // TODO: Sprite rendering using sprite sheet
    // TODO: Bounding box using lines
    // TODO: Player movement
    // TODO: AABB Collission
    // TODO: Player physics, like jumping and running
    // TODO: Sprite Animation

    m_camera.Move(dt, m_windowManager);
    m_camera.SetView();
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
        glfwPollEvents();

        m_windowWidth = m_window->width;
        m_windowHeight = m_window->height;

        if (m_windowManager.m_updateCamera) {
            m_camera.SetSize(glm::vec2(m_windowWidth, m_windowHeight));
            m_windowManager.SetUpdateCamera(false);
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        dt = glfwGetTime() - lastFrame;
        lastFrame = glfwGetTime();

        fps++;
        timeElapsed += dt;

        if (timeElapsed >= 1.0) {
            std::cout << "FPS: " << fps << std::endl;
            std::cout << "\033[2J\033[1;1H";
            fps = 0;
            timeElapsed = 0;
        }

        ProcessKeyTimeout(dt);
        ProcessInput(dt);

        Update(dt);

        Draw();

        glfwSwapBuffers(m_window->window);
    }
}

Application::~Application()
{
    std::cout << "Closing the Application" << std::endl;
    glfwDestroyWindow(m_window->window);
    glfwTerminate();
}
