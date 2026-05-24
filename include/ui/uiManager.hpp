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

        UiWidget* addUiWidget(std::unique_ptr<UiWidget> element);

    private:
        std::vector<std::unique_ptr<UiWidget>> uiWidgets;
};