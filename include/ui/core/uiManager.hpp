#pragma once

#include "core/idAllocator.hpp"
#include "rendering/material.hpp"
#include "ui/core/uiStructs.hpp"

#include <memory>
#include <vector>

class UiWidget;

class UiManager {
  public:
    unsigned int meshID;
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
    size_t totalMemory = 256 * sizeof(UiVertex) * 6;
    bool reloadUi = false;
    std::vector<bool> allocatedMemory;
    std::vector<std::unique_ptr<UiWidget>> uiWidgets;
    IDAllocator elementIDAllocator = IDAllocator(1024);
};