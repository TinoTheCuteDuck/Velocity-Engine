#include "ui/core/uiManager.hpp"

#include "core/engine.hpp"
#include "rendering/textureData.hpp"
#include "ui/core/engineUi.hpp"
#include "ui/widgets/uiWidget.hpp"

UiManager::UiManager() {
    uiWidgets.reserve(1024);
    allocatedMemory.resize(totalMemory, false);
}

UiManager::~UiManager() {
    uiWidgets.clear();
    if (meshID)
        Engine::get().renderer.deleteGPUMesh(meshID);
}

void UiManager::load() {
    AssetManager& assetManager = Engine::get().assetManager;

    if (meshID)
        Engine::get().renderer.deleteGPUMesh(meshID);

    uiWidgets.clear();
    allocatedMemory.clear();
    allocatedMemory.resize(totalMemory, false);
    loadUi();

    meshID = Engine::get().renderer.addGPUUiMesh(totalMemory);

    assetManager.loadShader(ASSETS_PATH "shaders/ui/uiVertexShader.vert", ASSETS_PATH "shaders/ui/uiFragmentShader.frag");
    assetManager.loadTexture(ASSETS_PATH "textures/JetBrainsMonoNerdFont-Regular-atlas.png", TextureWrapMode::ClampToEdge, TextureWrapMode::ClampToEdge, TextureWrapMode::ClampToEdge, TextureFilter::Linear, TextureFilter::Linear, false);

    material = Material{ASSETS_PATH "shaders/ui/uiVertexShader.vert", ASSETS_PATH "shaders/ui/uiFragmentShader.frag", {}};
    material.textures.emplace(std::make_pair("uiTexture", ASSETS_PATH "textures/JetBrainsMonoNerdFont-Regular-atlas.png"));
}

void UiManager::update() {
    if (reloadUi) {
        load();
        reloadUi = false;
    }

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
            for (size_t j = i; j < i + requiredMemory; j++) {
                if (j >= allocatedMemory.size()) {
                    freeRange = false;
                    break;
                }
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
    totalMemory *= 2.0f;
    reloadUi = true;
    return 0;
}