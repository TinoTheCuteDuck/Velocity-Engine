#pragma once

#include "ui/uiStructs.hpp"

#include <core/idAllocator.hpp>
#include <memory>
#include <rendering/material.hpp>
#include <ui/uiWidget.hpp>
#include <vector>

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

    template <typename T, typename... Args>
    std::shared_ptr<T> addUiWidget(Args&&... args) {
        auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
        uiWidgets.push_back(ptr);
        return ptr;
    }

    bool uiFocus = false;

  private:
    size_t totalMemory = 256 * sizeof(UiVertex) * 6;
    std::vector<bool> allocatedMemory;
    std::vector<std::shared_ptr<UiWidget>> uiWidgets;
    IDAllocator elementIDAllocator = IDAllocator(1024);
};