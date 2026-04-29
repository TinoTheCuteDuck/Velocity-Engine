#pragma once

#include <glad/glad.h>
#include <string>
#include <utility>

class Texture {
    private:
        unsigned int texture;
        int width, height, nrChannels;

    public:
        Texture(const std::string& filepath, GLenum wrapMode, GLenum filterMode, bool generateMipmaps);
        ~Texture();

        Texture(Texture&& other) noexcept
            : texture(std::exchange(other.texture, 0)) {}

        Texture& operator=(Texture&& other) noexcept {
            if (this != &other) {
                if (texture)
                    glDeleteTextures(1, &texture);

                texture = std::exchange(other.texture, 0);
            }
            return *this;
        }

        void bind(unsigned int slot);
};