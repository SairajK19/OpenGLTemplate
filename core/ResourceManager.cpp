#include "ResourceManager.h"

ResourceManager ResourceManager::Instance = ResourceManager();

ResourceManager::ResourceManager()
{
    root = std::filesystem::path(PROJECT_DIR_ROOT);
}

void ResourceManager::AddTexture(std::string path, std::string name)
{
    std::filesystem::path absolutePath = root / path;
    Texture tex = Texture();
    tex.LoadTexture(absolutePath);

    m_textures[name] = tex;
}

void ResourceManager::AddShader(std::string vsPath,
                                std::string fsPath,
                                std::string name,
                                ShaderType type)
{
    std::filesystem::path vsAbsolutePath = root / vsPath;
    std::filesystem::path fsAbsolutePath = root / fsPath;

    Shader shader = Shader(ShaderType::Default);
    shader.Compile(vsAbsolutePath.c_str(), fsAbsolutePath.c_str());

    m_shaders[name] = shader;
}

Texture ResourceManager::GetTexture(std::string name)
{
    auto it = m_textures.find(name);

    if (it == m_textures.end()) {
        // TODO: Think of some other way to handle this.
        exit(EXIT_FAILURE);
    }

    return it->second;
}

Shader &ResourceManager::GetShader(std::string name)
{
    auto it = m_shaders.find(name);

    if (it == m_shaders.end()) {
        // TODO: Think of some other way to handle this.
        exit(EXIT_FAILURE);
    }

    return it->second;
}

ResourceManager::~ResourceManager() { }