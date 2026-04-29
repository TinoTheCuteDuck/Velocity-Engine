#pragma once

#include <string>
#include <unordered_map>

struct Material {
        unsigned int shaderID;
        std::unordered_map<std::string, unsigned int> textures{};
};