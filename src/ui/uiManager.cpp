#include <glad/glad.h>
#include <memory>
#include <renderer.hpp>
#include <shader.hpp>
#include <uiElement.hpp>
#include <uiManager.hpp>

bool UiManager::staticElementsDirty = true;
bool UiManager::dynamicElementsDirty = true;
bool UiManager::staticTextDirty = true;
bool UiManager::dynamicTextDirty = true;

unsigned int UiManager::staticElementsVAO, UiManager::staticElementsVBO;
unsigned int UiManager::dynamicElementsVAO, UiManager::dynamicElementsVBO;
unsigned int UiManager::staticTextVAO, UiManager::staticTextVBO;
unsigned int UiManager::dynamicTextVAO, UiManager::dynamicTextVBO;

std::vector<UiVertex> UiManager::staticElementsVertexData;
std::vector<UiVertex> UiManager::dynamicElementsVertexData;
std::vector<UiVertex> UiManager::staticTextVertexData;
std::vector<UiVertex> UiManager::dynamicTextVertexData;

std::vector<std::unique_ptr<UiElement>> UiManager::staticElements;
std::vector<std::unique_ptr<UiElement>> UiManager::dynamicElements;
std::vector<std::unique_ptr<UiElement>> UiManager::staticText;
std::vector<std::unique_ptr<UiElement>> UiManager::dynamicText;

void UiManager::initBuffer(unsigned int& VAO, unsigned int& VBO) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void UiManager::buildBuffer(unsigned int VAO, unsigned int VBO, std::vector<UiVertex>& vertexData) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(UiVertex), vertexData.data(), GL_DYNAMIC_DRAW);
}

void UiManager::buildGeometry(std::vector<std::unique_ptr<UiElement>>& elements, std::vector<UiVertex>& vertexData) {
    vertexData.clear();
    for (std::unique_ptr<UiElement>& element : elements) {
        element->generateQuads(vertexData);
    }
}

void UiManager::init() {
    initBuffer(staticElementsVAO, staticElementsVBO);
    initBuffer(dynamicElementsVAO, dynamicElementsVBO);
    initBuffer(staticTextVAO, staticTextVBO);
    initBuffer(dynamicTextVAO, dynamicTextVBO);

    staticElementsVertexData.reserve(1024);
    dynamicElementsVertexData.reserve(1024);
    staticTextVertexData.reserve(4096);
    dynamicTextVertexData.reserve(4096);
}

void UiManager::submit(Renderer& renderer, Shader& uiShader) {
    if (staticElementsDirty) {
        buildGeometry(staticElements, staticElementsVertexData);
        buildBuffer(staticElementsVAO, staticElementsVBO, staticElementsVertexData);
        staticElementsDirty = false;
    }
    if (dynamicElementsDirty) {
        buildGeometry(dynamicElements, dynamicElementsVertexData);
        buildBuffer(dynamicElementsVAO, dynamicElementsVBO, dynamicElementsVertexData);
        dynamicElementsDirty = false;
    }
    if (staticTextDirty) {
        buildGeometry(staticText, staticTextVertexData);
        buildBuffer(staticTextVAO, staticTextVBO, staticTextVertexData);
        staticTextDirty = false;
    }
    if (dynamicTextDirty) {
        buildGeometry(dynamicText, dynamicTextVertexData);
        buildBuffer(dynamicTextVAO, dynamicTextVBO, dynamicTextVertexData);
        dynamicTextDirty = false;
    }

    renderer.renderQueue(RenderCall{
        &uiShader,
        staticElementsVAO,
        GL_TRIANGLES,
        0,
        staticElementsVertexData.size(),
        false});
    renderer.renderQueue(RenderCall{
        &uiShader,
        dynamicElementsVAO,
        GL_TRIANGLES,
        0,
        dynamicElementsVertexData.size(),
        false});
    renderer.renderQueue(RenderCall{
        &uiShader,
        staticTextVAO,
        GL_TRIANGLES,
        0,
        staticTextVertexData.size(),
        false});
    renderer.renderQueue(RenderCall{
        &uiShader,
        dynamicTextVAO,
        GL_TRIANGLES,
        0,
        dynamicTextVertexData.size(),
        false});
}

void UiManager::shutdown() {
    glDeleteVertexArrays(1, &staticElementsVAO);
    glDeleteVertexArrays(1, &dynamicElementsVAO);
    glDeleteVertexArrays(1, &staticTextVAO);
    glDeleteVertexArrays(1, &dynamicTextVAO);

    glDeleteBuffers(1, &staticElementsVBO);
    glDeleteBuffers(1, &dynamicElementsVBO);
    glDeleteBuffers(1, &staticTextVBO);
    glDeleteBuffers(1, &dynamicTextVBO);
}

UiElement* UiManager::addStaticElement(std::unique_ptr<UiElement> element) {
    staticElements.push_back(std::move(element));
    return staticElements.back().get();
}

UiElement* UiManager::addDynamicElement(std::unique_ptr<UiElement> element) {
    dynamicElements.push_back(std::move(element));
    return dynamicElements.back().get();
}

UiElement* UiManager::addStaticText(std::unique_ptr<UiElement> element) {
    staticText.push_back(std::move(element));
    return staticText.back().get();
}

UiElement* UiManager::addDynamicText(std::unique_ptr<UiElement> element) {
    dynamicText.push_back(std::move(element));
    return dynamicText.back().get();
}