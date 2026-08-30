#pragma once

#include "Utils.h"
#include "glm/glm.hpp"
#include "string"

#include <filesystem>

class SpriteSheet
{
private:
    float m_cellSize, m_atlasDimension;
    std::unordered_map<std::string, Sprite> m_slices;
    std::filesystem::path m_root;

public:
    SpriteSheet() { };
    SpriteSheet(std::string path, float cellSize);

    Sprite GetSprite(std::string name);
    glm::vec4 GetTextureCoord(Sprite s);

    void LoadMetadata(std::filesystem::path metadataPath);

    ~SpriteSheet();
};
