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

    std::function<void(std::shared_ptr<UiWidget>&)> assignIDs =
        [&](std::shared_ptr<UiWidget>& widget) {
            widget->offset = offset;
            offset += widget->memory;
            widget->elementID = elementID++;

            for (auto& child : widget->children) {
                assignIDs(child);
            }
        };

    for (auto& widget : uiWidgets) {
        assignIDs(widget);
    }

    meshID = Engine::get().renderer.addGPUUiMesh(offset);

    material = Material{Ressources::uiShader};
    material.textures["uiTexture"] = Ressources::uiTexture;
}

void UiManager::update() {
    size_t vertexCount = 0;

    std::function<void(std::shared_ptr<UiWidget>&)> updateRecursive =
        [&](std::shared_ptr<UiWidget>& widget) {
            widget->update();
            vertexCount += widget->vertexCount;

            for (auto& child : widget->children) {
                updateRecursive(child);
            }
        };

    for (auto& widget : uiWidgets) {
        updateRecursive(widget);
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