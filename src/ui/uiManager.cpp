#include "engineContext.hpp"
#include "shader.hpp"
#include <ui/uiManager.hpp>

UiManager::UiManager() : VAO(0), VBO(0), texture(0), vertexCount(0) {
    addUiElement(Vector2(), Vector2(100, 300), Vector3(200, 0, 0), Vector2());
    generateUiMesh();
}

UiManager::~UiManager() {
    clear();
}

void UiManager::addUiElement(const Vector2& position, const Vector2& size, const Vector3& color, const Vector2& UV) {
    uiElements.push_back(UiElement{position, size, color, UV});
}

void UiManager::generateUiMesh() {
    std::vector<UiVertex> vertexData;
    for (const UiElement& obj : uiElements) {
        float leftX = ((obj.position.x / gEngineContext.width) * 2.0f) - 1.0f;
        float rightX = (((obj.position.x + obj.size.x) / gEngineContext.width) * 2.0f) - 1.0f;
        float topY = -(((obj.position.y / gEngineContext.height) * 2.0f) - 1.0f);
        float bottomY = -((((obj.position.y + obj.size.y) / gEngineContext.height) * 2.0f) - 1.0f);

        vertexData.push_back(UiVertex{Vector2(leftX, bottomY), obj.color, obj.UV});
        vertexData.push_back(UiVertex{Vector2(rightX, bottomY), obj.color, obj.UV});
        vertexData.push_back(UiVertex{Vector2(leftX, topY), obj.color, obj.UV});

        vertexData.push_back(UiVertex{Vector2(rightX, bottomY), obj.color, obj.UV});
        vertexData.push_back(UiVertex{Vector2(rightX, topY), obj.color, obj.UV});
        vertexData.push_back(UiVertex{Vector2(leftX, topY), obj.color, obj.UV});
    }
    vertexCount = vertexData.size();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(UiVertex) * vertexData.size(), vertexData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void UiManager::draw() {
    gEngineContext.uiShader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}

void UiManager::clear() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    uiElements.clear();
}