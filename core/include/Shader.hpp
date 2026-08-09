#pragma once

#include <string>

#include <glad/glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>

enum class ShaderType { Default, Texture };

class Shader
{
private:
    unsigned int shaderProgram;
    ShaderType m_type;
    void ReadShaders(const char *vsPath,
                     const char *fsPath,
                     std::string &vsSource,
                     std::string &fsSource);

public:
    Shader(ShaderType type = ShaderType::Default);
    void Compile(const char *vertexShaderSource, const char *fragmentShaderSource);
    void Use();
    void SetFloat(const std::string &name, float val);
    void SetInt(const std::string &name, int val);
    void SetVec2f(const std::string &name, glm::vec2 vec);
    void SetVec3f(const std::string &name, glm::vec3 vec);
    void SetVec4f(const std::string &name, glm::vec4 vec);
    void SetMat4(const std::string &name, glm::mat4 mat4);
    ShaderType GetType();
    ~Shader();
};
