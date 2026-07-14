#pragma once

#include "core/idAllocator.hpp"
#include "rendering/renderingTypes.hpp"
#include "ui/core/uiTypes.hpp"

#include <memory>
#include <vector>

class UiWidget;

class UiManager {
  public:
    unsigned int meshID = 0;
    Material material;

    UiManager();
    ~UiManager();

    void load();
    void update();
    void submit();
    void reRender();
    void freeMemory(const unsigned int elementID, const size_t offset, const size_t allocatedMemory);
    void allocateMemory(UiWidget* widget);
    size_t getLowestMemoryRegion(const size_t requiredMemory);

    template <typename T>
    T* addUiWidget() {
        auto ptr = std::make_unique<T>();
        T* raw = ptr.get();
        uiWidgets.push_back(std::move(ptr));
        return raw;
    }

    bool uiFocus = false;

  private:
    bool reloadUi = false;

    size_t totalMemory = 3600;
    size_t lastFreeMemory = 0;

    std::vector<bool> allocatedMemory;
    std::vector<std::unique_ptr<UiWidget>> uiWidgets;
    IDAllocator elementIDAllocator = IDAllocator(1024);
};