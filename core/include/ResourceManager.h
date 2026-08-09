#pragma once

#include "Shader.hpp"
#include "Texture.hpp"
#include "string"
#include "unordered_map"
#include <filesystem>
#include <optional>

class ResourceManager
{
private:
    std::unordered_map<std::string, Texture> m_textures;
    std::unordered_map<std::string, Shader> m_shaders;
    std::filesystem::path root;

public:
    ResourceManager();

    static ResourceManager Instance;

    void AddTexture(std::string path, std::string name);
    void AddShader(std::string vsPath, std::string fsPath, std::string name, ShaderType type);

    Texture GetTexture(std::string name);
    Shader &GetShader(std::string name);

    ~ResourceManager();
};
