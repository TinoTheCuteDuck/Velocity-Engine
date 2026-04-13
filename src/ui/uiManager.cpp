#include <engineContext.hpp>
#include <glad/glad.h>
#include <memory>
#include <texture.hpp>
#include <uiManager.hpp>
#include <uiText.hpp>
#include <vector>

std::vector<std::unique_ptr<UiElement>> UiManager::uiElements;
unsigned int UiManager::VAO, UiManager::VBO;
std::unique_ptr<Texture> UiManager::uiTexture;
int UiManager::vertexSize = 0;

void UiManager::init() {
    addUiElement(std::make_unique<UiText>(Vector2(100, 100), Vector3(0.8, 0.8, 0.8), "Hello World", 32));
    uiTexture = std::make_unique<Texture>(ASSETS_PATH "textures/DejaVu Sans Mono.png", GL_REPEAT, GL_NEAREST, false);

    gEngineContext.uiShader->use();
    gEngineContext.uiShader->setInt("uiTexture", 0);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    buildUiMesh();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void UiManager::buildUiMesh() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    std::vector<UiVertex> vertexData;

    for (std::unique_ptr<UiElement>& obj : uiElements) {
        obj->generateQuads(vertexData);
    }
    vertexSize = vertexData.size();

    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(UiVertex), vertexData.data(), GL_DYNAMIC_DRAW);
}

void UiManager::addUiElement(std::unique_ptr<UiElement> element) {
    uiElements.push_back(std::move(element));
}

void UiManager::draw() {
    uiTexture->bind(0);
    gEngineContext.uiShader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexSize);
    glBindVertexArray(0);
}