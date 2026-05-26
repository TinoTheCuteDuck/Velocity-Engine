#include <ui/uiManager.hpp>

#include <core/engine.hpp>
#include <core/ressources.hpp>

#include <rendering/material.hpp>

#include <ui/engineUi.hpp>
#include <ui/uiWidget.hpp>

#include <memory>

UiManager::UiManager() {
    uiWidgets.reserve(1024);
}

UiManager::~UiManager() {
    Engine::get().renderer.deleteGPUMesh(meshID);
}

void UiManager::load() {
    Engine::get().renderer.deleteGPUMesh(meshID);
    uiWidgets.clear();
    loadUi();

    size_t offset = 0;
    unsigned int elementID = 0;
    for (auto& uiWidget : uiWidgets) {
        uiWidget->offset = offset;
        offset += uiWidget->memory;
        uiWidget->elementID = elementID;
        elementID++;
    }
    meshID = Engine::get().renderer.addGPUUiMesh(offset);
    material = Material{Ressources::uiShader};
    material.textures["uiTexture"] = Ressources::uiTexture;
}

void UiManager::update() {
    size_t vertexCount = 0;

    for (std::shared_ptr<UiWidget>& widget : uiWidgets) {
        widget->update();
        vertexCount += widget->vertexCount;
    }
    Engine::get().renderer.changeGPUVertexCount(meshID, vertexCount);
}

void UiManager::submit() {
    Engine::get().renderer.renderQueue(RenderCall{
        meshID,
        material,
        std::nullopt,
        false});
}

void UiManager::reRender() {
    for (auto& uiWidget : uiWidgets) {
        uiWidget->dirty = true;
    }
}

template <typename T, typename... Args>
std::shared_ptr<T> UiManager::addUiWidget(Args&&... args) {
    auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
    uiWidgets.push_back(ptr);
    return ptr;
}