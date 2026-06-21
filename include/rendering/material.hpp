#pragma once

#include <string>
#include <unordered_map>

struct Material {
    std::string vertexPath;
    std::string fragmentPath;

    std::unordered_map<std::string, std::string> textures;
};