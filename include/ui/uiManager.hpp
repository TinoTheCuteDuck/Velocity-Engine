#pragma once

#include <rendering/material.hpp>
#include <ui/uiWidget.hpp>

#include <memory>
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

        template <typename T, typename... Args>
        std::shared_ptr<T> addUiWidget(Args&&... args) {
            auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
            uiWidgets.push_back(ptr);
            return ptr;
        }

    private:
        std::vector<std::shared_ptr<UiWidget>> uiWidgets;
};