#pragma once

#include "GLFW/glfw3.h"
#include "math/vector/vector2.hpp"

#include <string>

class Window {
  public:
    Window();
    ~Window();

    void pollEvents() const;
    [[nodiscard]] bool shouldClose() const;

    bool getVsync();
    [[nodiscard]] Vector2 getWindowSize() const;
    [[nodiscard]] GLFWwindow* getWindow() const;
    [[nodiscard]] bool getVsync() const;
    std::string& getTitle();

    static void setVsync(bool enabled);
    void setWindowSize(int width, int height);

  private:
    bool vsync = true;
    std::string title = "Velocity Engine";
    Vector2 windowSize = Vector2(1920, 1080);

    GLFWwindow* window;
};