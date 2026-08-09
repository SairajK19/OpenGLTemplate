#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(ShaderType type)
    : m_type(type)
{ }

void Shader::ReadShaders(const char *vsPath,
                         const char *fsPath,
                         std::string &vsSource,
                         std::string &fsSource)
{
    std::ifstream vs(vsPath);
    if (!vs.is_open()) {
        std::cerr << "Failed to open vertex shader at: " << vsPath;
        exit(EXIT_FAILURE);
    }

    std::stringstream vsBuff;
    vsBuff << vs.rdbuf();
    vsSource = vsBuff.str();

    std::ifstream fs(fsPath);
    if (!fs.is_open()) {
        std::cerr << "Failed to open fragment shader at: " << fsPath;
        exit(EXIT_FAILURE);
    }

    std::stringstream fsBuff;
    fsBuff << fs.rdbuf();
    fsSource = fsBuff.str();
}

void Shader::Compile(const char *vsPath, const char *fsPath)
{
    std::string vsSource, fsSource;
    int success;
    char logInfo[1000];

    ReadShaders(vsPath, fsPath, vsSource, fsSource);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char *vss = vsSource.c_str();
    glShaderSource(vertexShader, 1, &vss, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 1000, NULL, logInfo);
        std::cerr << "Failed to compile vertex shader.. Error:" << logInfo << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *fss = fsSource.c_str();
    glShaderSource(fragmentShader, 1, &fss, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 1000, NULL, logInfo);
        std::cerr << "Failed to compile fragment shader.. Error:" << logInfo << std::endl;
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 1000, NULL, logInfo);
        std::cerr << "Failed to linke shader program. Error: " << logInfo << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::SetFloat(const std::string &name, float val)
{
    glProgramUniform1f(shaderProgram, glGetUniformLocation(shaderProgram, name.c_str()), val);
}

void Shader::SetInt(const std::string &name, int val)
{
    glProgramUniform1i(shaderProgram, glGetUniformLocation(shaderProgram, name.c_str()), val);
}

void Shader::SetVec2f(const std::string &name, glm::vec2 vec)
{
    glProgramUniform2f(shaderProgram, glGetUniformLocation(shaderProgram, name.c_str()), vec.x, vec.y);
}

void Shader::SetVec3f(const std::string &name, glm::vec3 vec)
{
    glProgramUniform3f(shaderProgram, glGetUniformLocation(shaderProgram, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader::SetVec4f(const std::string &name, glm::vec4 vec)
{
    glProgramUniform4f(shaderProgram, glGetUniformLocation(shaderProgram, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetMat4(const std::string &name, glm::mat4 mat4)
{
    glProgramUniformMatrix4fv(shaderProgram, glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
}

ShaderType Shader::GetType()
{
    return m_type;
}

void Shader::Use()
{
    glUseProgram(shaderProgram);
}

Shader::~Shader() { }