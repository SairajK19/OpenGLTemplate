#pragma once

#include "Utils.h"
#include <vector>

class Mesh
{
protected:
    unsigned int m_vao, m_vbo, m_ebo;

public:
    virtual void Init() = 0;
    virtual void Bind() = 0;
};