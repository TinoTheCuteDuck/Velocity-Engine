#include <uiManager.hpp>

#include <material.hpp>
#include <renderer.hpp>
#include <ressources.hpp>
#include <uiElement.hpp>

#include <memory>

UiManager::UiManager() {
    vertexData.reserve(8192);
    uiElements.reserve(1024);
}

void UiManager::load() {
    buildGeometry();
    meshID = Renderer::get().addGPUUiMesh(vertexData);
    material = Material{Ressources::uiShader};
    material.textures["uiTexture"] = Ressources::uiTexture;
}

void UiManager::update() {
    for (std::unique_ptr<UiElement>& element : uiElements) {
        element->update();
    }
    buildGeometry();
    Renderer::get().changeGPUUiMeshData(meshID, vertexData);
}

void UiManager::submit() {
    Renderer::get().renderQueue(RenderCall{
        meshID,
        material});
}

void UiManager::setInstance(UiManager& uiManager) {
    instance = &uiManager;
}

UiManager& UiManager::get() {
    if (!instance) {
        throw std::runtime_error("UiManager not initialized!");
    }
    return *instance;
}

UiElement* UiManager::addUiElement(std::unique_ptr<UiElement> element) {
    uiElements.push_back(std::move(element));
    return uiElements.back().get();
}

void UiManager::buildGeometry() {
    vertexData.clear();
    for (std::unique_ptr<UiElement>& element : uiElements) {
        element->generateQuads(vertexData);
    }
}