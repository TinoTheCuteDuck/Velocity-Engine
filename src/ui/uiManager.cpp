#include <uiManager.hpp>

#include <engine.hpp>
#include <material.hpp>
#include <ressources.hpp>
#include <uiElement.hpp>

#include <memory>

UiManager::UiManager() {
    vertexData.reserve(8192);
    uiElements.reserve(1024);
}

void UiManager::load() {
    buildGeometry();
    meshID = Engine::get().renderer.addGPUUiMesh(vertexData);
    material = Material{Ressources::uiShader};
    material.textures["uiTexture"] = Ressources::uiTexture;
}

void UiManager::update() {
    for (std::unique_ptr<UiElement>& element : uiElements) {
        element->update();
    }
    buildGeometry();
    Engine::get().renderer.changeGPUUiMeshData(meshID, vertexData);
}

void UiManager::submit() {
    Engine::get().renderer.renderQueue(RenderCall{
        meshID,
        material});
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