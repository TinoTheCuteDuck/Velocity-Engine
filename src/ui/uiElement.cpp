#include <ui/uiElement.hpp>

UiObject::UiObject(const float x, const float y, const float sizeX, const float sizeY, const std::string& texturePath) {
    vertices = {
        x, y - sizeY, 0.0f,         0.0f, 0.0f,     0.8f, 0.8f, 0.8f,
        x + sizeX, y - sizeY, 0.0f, 1.0f, 0.0f,     0.8f, 0.8f, 0.8f,
        x + sizeX, y, 0.0f,         1.0f, 1.0f,     0.8f, 0.8f, 0.8f,
        x, y, 0.0f,                 0.0f, 1.0f,     0.8f, 0.8f, 0.8f,
    };

    indices = {
        0, 1, 2,    0, 2, 3
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

UiObject::~UiObject() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void UiObject::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}