#include "QuadMesh.h"

#include <glad/glad.h>
#include <glfw3.h>

QuadMesh::QuadMesh() { }

void QuadMesh::Init()
{
    std::vector<ColorVertex> vertices;

    ColorVertex a = {{1.0f, 1.0f, 0.0f}, {1.0, 0.0, 0.0, 1.0}};
    ColorVertex b = {{1.0f, 0.0f, 0.0f}, {0.0, 1.0, 0.0, 1.0}};
    ColorVertex c = {{0.0f, 0.0f, 0.0f}, {0.0, 0.0, 1.0, 1.0}};
    ColorVertex d = {{0.0f, 1.0f, 0.0f}, {0.0, 1.0, 1.0, 1.0}};

    vertices.assign({a, b, c, d});

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    unsigned int m_ebo;
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

    m_indices.assign({0, 2, 3, 0, 1, 2});

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(ColorVertex),
                 vertices.data(),
                 GL_STATIC_DRAW);

    int locationPos = 0;
    glVertexAttribPointer(locationPos, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void *) 0);
    glEnableVertexAttribArray(locationPos);

    int locationColor = 1;
    glVertexAttribPointer(locationColor,
                          4,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(ColorVertex),
                          (void *) (offsetof(ColorVertex, color)));
    glEnableVertexAttribArray(locationColor);
}

std::vector<unsigned int> QuadMesh::GetIndices()
{
    return m_indices;
}

void QuadMesh::Bind()
{
    glBindVertexArray(m_vao);
}

QuadMesh::~QuadMesh() { }