#pragma once

#include "Shader.hpp"
#include "SpriteSheet.h"
#include "Texture.hpp"

#include <filesystem>
#include <optional>
#include <string>
#include <unordered_map>

class ResourceManager
{
private:
    std::unordered_map<std::string, Texture> m_textures;
    std::unordered_map<std::string, Shader> m_shaders;
    std::unordered_map<std::string, SpriteSheet> m_spriteSheets;
    std::filesystem::path root;

public:
    ResourceManager();

    static ResourceManager Instance;

    void AddTexture(std::string path, std::string name);
    void AddShader(std::string vsPath, std::string fsPath, std::string name, ShaderType type);
    void AddSpriteSheet(std::string path, std::string name);

    Texture GetTexture(std::string name);
    Shader &GetShader(std::string name);
    SpriteSheet &GetSpriteSheet(std::string name);

    ~ResourceManager();
};
