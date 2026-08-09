#include "SpriteRenderer.h"

#include <glad/glad.h>
#include <glfw3.h>
#include <vector>

#include "Constants.h"
#include "ResourceManager.h"

SpriteRenderer::SpriteRenderer() { }

void SpriteRenderer::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    textureMesh.Init();
    quadMesh.Init();
}

void SpriteRenderer::DrawQuad(glm::vec2 pos, glm::vec2 dimensions)
{
    Shader shader = ResourceManager::Instance.GetShader(DEFAULT_SHADER);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * dimensions.x, 0.5f * dimensions.y, 0.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * dimensions.x, -0.5f * dimensions.y, 0.0f));

    model = glm::scale(model, glm::vec3(dimensions, 0.0f));

    quadMesh.Bind();
    shader.Use();
    shader.SetMat4("model", model);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

/***
 * TODO: Support ability to have multiple meshes. Currently it renderes all the instances as a single mesh.
 * This is problematic incase you have a scene in which a texture is drawn behind another texture in some area
 * as well as drawn infront in some other area.
*/
void SpriteRenderer::DrawSprite(Texture &texture, glm::vec2 pos, glm::vec2 dimensions, glm::vec4 texCoord, glm::vec4 color, float angle)
{
    Shader shader = ResourceManager::Instance.GetShader(TEXTURE_SHADER);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * dimensions.x, 0.5f * dimensions.y, 0.0f));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * dimensions.x, -0.5f * dimensions.y, 0.0f));

    model = glm::scale(model, glm::vec3(dimensions, 0.0f));

    InstanceData instance;
    instance.modelMatrix = model;
    instance.color = color;

    instance.texUv = texCoord;
    textureMesh.PushInstance(texture.GetTexture(), instance);
}

void SpriteRenderer::Begin()
{
    textureMesh.ClearInstances();
}

void SpriteRenderer::End()
{
    std::map<TextureID, std::vector<InstanceData>> items = textureMesh.GetItems();

    for (const auto &[textureId, data] : items) {
        glBindTexture(GL_TEXTURE_2D, textureId);
        textureMesh.LoadInstances(textureId);
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, textureMesh.GetInstanceCount(textureId));
    }
}

SpriteRenderer::~SpriteRenderer() { }