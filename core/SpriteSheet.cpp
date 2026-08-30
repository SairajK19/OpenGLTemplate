#include "SpriteSheet.h"

#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

SpriteSheet::SpriteSheet(std::string path, float cellSize)
    : m_cellSize(cellSize)
{
    LoadMetadata(path);
}

void SpriteSheet::LoadMetadata(std::filesystem::path metadataPath)
{
    std::ifstream f(metadataPath);
    json data = json::parse(f);

    json slices = data["meta"]["slices"];
    json size = data["meta"]["size"];
    float atlasW = size["w"];
    float atlasH = size["h"];

    for (auto &slice : slices) {
        std::string sliceName = slice["name"];
        json key = slice["keys"][0];
        json bounds = key["bounds"];

        SpriteCoord sc = SpriteCoord();
        float x = bounds["x"];
        float y = bounds["y"];
        float w = bounds["w"];
        float h = bounds["h"];

        glm::vec2 topLeft = {x / m_cellSize, y / m_cellSize};
        glm::vec2 bottomRight = {topLeft.x + (w / m_cellSize), topLeft.y + (h / m_cellSize)};

        sc.topLeft = topLeft * (m_cellSize / atlasW);
        sc.bottomRight = bottomRight * (m_cellSize / atlasH);

        Sprite s = Sprite();
        s.coord = sc;
        s.w = bounds["w"];
        s.h = bounds["h"];

        m_slices[slice["name"]] = s;
    }
}

Sprite SpriteSheet::GetSprite(std::string name)
{
    return m_slices[name];
}

glm::vec4 SpriteSheet::GetTextureCoord(Sprite s)
{
    return glm::vec4(s.coord.topLeft, s.coord.bottomRight);
}

SpriteSheet::~SpriteSheet() { }