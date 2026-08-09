#pragma once

#include "Mesh.h"

class QuadMesh : public Mesh
{
private:
    std::vector<unsigned int> m_indices;

public:
    QuadMesh();

    void Init();
    void Bind();

    std::vector<unsigned int> GetIndices();

    ~QuadMesh();
};
