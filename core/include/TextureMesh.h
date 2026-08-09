#pragma once

#include "Mesh.h"
#include "Utils.h"
#include "glm/gtc/matrix_transform.hpp"
#include <map>
#include <string>

struct InstanceData
{
    glm::mat4 modelMatrix;
    glm::vec4 texUv;
    glm::vec4 color;
};

class TextureMesh : public Mesh
{
private:
    unsigned int m_instanceBuffer;

    // Key = Texture Id
    std::map<TextureID, std::vector<InstanceData>> m_items;

public:
    TextureMesh();

    void Init();
    void Bind();

    void PushInstance(TextureID textureId, InstanceData instance);
    void LoadInstances(TextureID textureId);

    void ClearInstances();

    std::map<TextureID, std::vector<InstanceData>> &GetItems();
    unsigned int GetInstanceCount(TextureID textureId);
};
