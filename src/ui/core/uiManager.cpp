#include "ui/core/uiManager.hpp"

#include "core/engine.hpp"
#include "rendering/textureData.hpp"
#include "ui/core/engineUi.hpp"
#include "ui/core/uiTypes.hpp"
#include "ui/widgets/uiWidget.hpp"

UiManager::UiManager() {
    uiWidgets.reserve(1024);
    allocatedMemory.resize(totalMemory, false);
}

UiManager::~UiManager() {
    uiWidgets.clear();
    if (meshID) Engine::get().renderer.deleteGPUMesh(meshID);
}

void UiManager::load() {
    AssetManager& assetManager = Engine::get().assetManager;

    if (meshID) Engine::get().renderer.deleteGPUMesh(meshID);

    uiWidgets.clear();
    allocatedMemory.clear();
    allocatedMemory.resize(totalMemory, false);
    loadUi();
    std::cout << "Reloading Ui" << std::endl;

    meshID = Engine::get().renderer.addGPUUiMesh(totalMemory * sizeof(UiVertex));

    assetManager.loadShader(ASSETS_PATH "shaders/ui/uiVertexShader.vert", ASSETS_PATH "shaders/ui/uiFragmentShader.frag");
    assetManager.loadTexture(ASSETS_PATH "textures/JetBrainsMonoNerdFont-Regular-atlas.png", TextureWrapMode::ClampToEdge, TextureWrapMode::ClampToEdge, TextureWrapMode::ClampToEdge, TextureFilter::Linear, TextureFilter::Linear, false);

    material = Material{ASSETS_PATH "shaders/ui/uiVertexShader.vert", ASSETS_PATH "shaders/ui/uiFragmentShader.frag", ASSETS_PATH "textures/JetBrainsMonoNerdFont-Regular-atlas.png", "", "", "", ""};
}

void UiManager::update() {
    if (reloadUi) {
        load();
        reloadUi = false;
    }

    for (const auto& widget : uiWidgets) {
        widget->update();
    }
}

void UiManager::submit() const {
    Engine::get().renderer.renderQueue(RenderCall{
        meshID,
        0,
        material,
        std::nullopt,
        false});
}

void UiManager::reRender() const {
    for (auto& uiWidget : uiWidgets) {
        uiWidget->dirty = true;
    }
}

void UiManager::freeMemory(const unsigned int elementID, const size_t offset, const size_t memory) {
    if (reloadUi)
        return;

    elementIDAllocator.free(elementID);
    const size_t vertexOffset = offset / sizeof(UiVertex);
    const size_t vertexMemory = memory / sizeof(UiVertex);

    for (size_t i = vertexOffset; i < vertexOffset + vertexMemory; i++) {
        allocatedMemory.at(i) = false;
    }

    lastFreeMemory = vertexOffset;
}

void UiManager::allocateMemory(UiWidget* widget) {
    if (reloadUi) {
        widget->elementID = 0;
        return;
    }

    const unsigned int elementID = elementIDAllocator.allocate();
    widget->elementID = elementID;

    size_t verticesOffset = getLowestMemoryRegion(widget->memory);
    size_t vertexMemory = widget->memory / sizeof(UiVertex);
    widget->offset = verticesOffset * sizeof(UiVertex);

    for (size_t i = verticesOffset; i < verticesOffset + vertexMemory; i++) {
        allocatedMemory.at(i) = true;
    }

    lastFreeMemory = verticesOffset + vertexMemory;
}

size_t UiManager::getLowestMemoryRegion(const size_t requiredMemory) {
    if (reloadUi)
        return 0;

    const size_t requiredVerticesMemory = requiredMemory / sizeof(UiVertex);

    for (size_t i = lastFreeMemory; i < allocatedMemory.size(); i++) {
        if (allocatedMemory.at(i) == false) {
            bool freeRange = true;
            for (size_t j = i; j < i + requiredVerticesMemory; j++) {
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

    for (size_t i = 0; i < allocatedMemory.size(); i++) {
        if (allocatedMemory.at(i) == false) {
            bool freeRange = true;
            for (size_t j = i; j < i + requiredVerticesMemory; j++) {
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
    totalMemory *= 2;
    reloadUi = true;
    return 0;
}