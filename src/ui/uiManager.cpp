#include <mat4.hpp>
#include <material.hpp>
#include <memory>
#include <renderer.hpp>
#include <ressources.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <uiElement.hpp>
#include <uiManager.hpp>

void UiManager::init() {
    buildGeometry();
    meshID = Renderer::get().addGPUUiMesh(vertexData);
    material = Material{Ressources::uiShader};
    material.textures["uiTexture"] = Ressources::uiTexture;

    vertexData.reserve(8192);
    uiElements.reserve(1024);
}

void UiManager::buildGeometry() {
    vertexData.clear();
    for (std::unique_ptr<UiElement>& element : uiElements) {
        element->generateQuads(vertexData);
    }
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

UiElement* UiManager::addUiElement(std::unique_ptr<UiElement> element) {
    uiElements.push_back(std::move(element));
    return uiElements.back().get();
}