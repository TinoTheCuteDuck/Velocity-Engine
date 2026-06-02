#include <core/engine.hpp>
#include <core/ressources.hpp>
#include <rendering/material.hpp>
#include <ui/engineUi.hpp>
#include <ui/uiManager.hpp>
#include <ui/uiStructs.hpp>
#include <ui/uiWidget.hpp>

UiManager::UiManager() {
    std::cout << "Size: " << sizeof(UiVertex) << std::endl;
    uiWidgets.reserve(1024);
    allocatedMemory.resize(totalMemory, false);
}

UiManager::~UiManager() {
    Engine::get().renderer.deleteGPUMesh(meshID);
}

void UiManager::load() {
    Engine::get().renderer.deleteGPUMesh(meshID);
    uiWidgets.clear();
    allocatedMemory.resize(totalMemory, false);
    loadUi();

    meshID = Engine::get().renderer.addGPUUiMesh(totalMemory);

    material = Material{Ressources::uiShader};
    material.textures["uiTexture"] = Ressources::uiTexture;
}

void UiManager::update() {
    for (auto& widget : uiWidgets) {
        widget->update();
    }
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

void UiManager::freeMemory(const unsigned int elementID, const size_t offset, const size_t memory) {
    elementIDAllocator.free(elementID);
    for (size_t i = offset; i < offset + memory; i++) {
        allocatedMemory.at(i) = false;
    }
}

void UiManager::allocateMemory(UiWidget* widget) {
    unsigned int elementID = elementIDAllocator.allocate();
    widget->elementID = elementID;
    size_t offset = getLowestMemoryRegion(widget->memory);
    widget->offset = offset;
    for (size_t i = offset; i < offset + widget->memory; i++) {
        allocatedMemory.at(i) = true;
    }
}

size_t UiManager::getLowestMemoryRegion(const size_t requiredMemory) {
    for (size_t i = 0; i < allocatedMemory.size(); i++) {
        if (allocatedMemory.at(i) == false) {
            bool freeRange = true;
            for (size_t j = i; j < i + requiredMemory && j < allocatedMemory.size(); j++) {
                if (allocatedMemory.at(j) == true) {
                    freeRange = false;
                    break;
                }
            }
            if (freeRange == true) {
                return i;
            }
        }
    }
    totalMemory *= 1.5f;
    load();
    return 0;
}