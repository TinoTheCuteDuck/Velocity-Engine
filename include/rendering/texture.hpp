#pragma once

#include <glad/glad.h>
#include <string>

class Texture {
    private:
        unsigned int texture;
        int width, height, nrChannels;

    public:
        Texture(const std::string& filepath, GLenum wrapMode, GLenum filterMode, bool generateMipmaps);
        ~Texture();
        void bind(unsigned int slot);
};