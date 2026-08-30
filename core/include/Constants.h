#pragma once

#include <glm.hpp>
#include <string>

const glm::vec4 RED = glm::vec4(1.0, 0.0, 0.0, 1.0);
const glm::vec4 GREEN = glm::vec4(0.0, 1.0, 0.0, 1.0);
const glm::vec4 BLUE = glm::vec4(0.0, 0.0, 1.0, 1.0);
const glm::vec4 YELLOW = glm::vec4(1.0, 1.0, 0.0, 1.0);

// CONSTANTS

// Shaders
const std::string DEFAULT_SHADER = "DefaultShader";
const std::string TEXTURE_SHADER = "TextureShader";

// Textures
const std::string SOLAIRE_OF_ASTORA = "SolaireOfAstora";
const std::string DUNGEON_ATLAS = "DungeonAtlas";