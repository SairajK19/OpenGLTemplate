#include "TextureMesh.h"

#include <glad/glad.h>
#include <glfw3.h>

TextureMesh::TextureMesh() { }

void TextureMesh::Init()
{
    std::vector<TextureVertex> vertices;

    TextureVertex a = {{1.0f, 1.0f, 0.0f}, {1.0, 1.0, 1.0, 0.0}, {1.0f, 1.0f}};
    TextureVertex b = {{1.0f, 0.0f, 0.0f}, {1.0, 1.0, 1.0, 0.0}, {1.0f, 0.0f}};
    TextureVertex c = {{0.0f, 0.0f, 0.0f}, {1.0, 1.0, 1.0, 0.0}, {0.0f, 0.0f}};
    TextureVertex d = {{0.0f, 1.0f, 0.0f}, {1.0, 1.0, 1.0, 0.0}, {0.0f, 1.0f}};

    vertices.assign({a, b, c, d});

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    unsigned int m_ebo;
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

    std::vector<unsigned int> indices;
    indices.assign({0, 2, 3, 0, 1, 2});

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(TextureVertex),
                 vertices.data(),
                 GL_STATIC_DRAW);

    int locationPos = 0;
    glVertexAttribPointer(locationPos, 3, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void *) 0);
    glEnableVertexAttribArray(locationPos);

    int locationColor = 1;
    glVertexAttribPointer(locationColor,
                          4,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(TextureVertex),
                          (void *) (offsetof(TextureVertex, color)));
    glEnableVertexAttribArray(locationColor);

    int locationTexUV = 2;
    glVertexAttribPointer(locationTexUV,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(TextureVertex),
                          (void *) (offsetof(TextureVertex, uv)));
    glEnableVertexAttribArray(locationTexUV);

    glGenBuffers(1, &m_instanceBuffer);

    vertices.clear();
    indices.clear();
}

void TextureMesh::PushInstance(TextureID textureId, InstanceData instance)
{
    auto it = m_items.find(textureId);

    if (it != m_items.end()) {
        it->second.push_back(instance);
    } else {
        std::vector<InstanceData> d;
        d.push_back(instance);
        m_items[textureId] = d;
    }
}

std::map<TextureID, std::vector<InstanceData>> &TextureMesh::GetItems()
{
    return m_items;
}

void TextureMesh::LoadInstances(TextureID textureId)
{
    std::vector<InstanceData> &instances = m_items.at(textureId);
    Bind();
    glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(InstanceData) * instances.size(),
                 instances.data(),
                 GL_STATIC_DRAW);

    const std::size_t modelOffset = offsetof(InstanceData, modelMatrix);

    for (GLuint column = 0; column < 4; ++column) {
        GLuint location = 3 + column;

        glEnableVertexAttribArray(location);

        glVertexAttribPointer(location,
                              4,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(InstanceData),
                              reinterpret_cast<void *>(modelOffset + column * sizeof(glm::vec4)));

        glVertexAttribDivisor(location, 1);
    }

    int locationTexUv = 7;
    glVertexAttribPointer(locationTexUv,
                          4,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(InstanceData),
                          (void *) (offsetof(InstanceData, texUv)));
    glEnableVertexAttribArray(locationTexUv);

    glVertexAttribDivisor(locationTexUv, 1);

    int locationColor = 8;
    glVertexAttribPointer(locationColor, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void *) (offsetof(InstanceData, color)));
    glEnableVertexAttribArray(locationColor);

    glVertexAttribDivisor(locationColor, 1);
}

TextureID TextureMesh::GetInstanceCount(TextureID textureId)
{
    auto it = m_items.find(textureId);

    if (it != m_items.end()) {
        return it->second.size();
    } else {
        return 0;
    }
}

void TextureMesh::ClearInstances()
{
    for (auto &[textureId, data] : m_items) {
        data.clear();
    }
}

void TextureMesh::Bind()
{
    glBindVertexArray(m_vao);
}