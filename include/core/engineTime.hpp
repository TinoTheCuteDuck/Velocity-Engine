#pragma once

#include <chrono>

using clockVariant = std::chrono::high_resolution_clock;
using time_point = clockVariant::time_point;
using duration = std::chrono::duration<float>;

class EngineTime {
  public:
    void update();

    int getFPS() const;
    float getDt() const;
    float getTotal() const;

  private:
    int fps = 0;
    int frames = 0;

    float dt = 0.0f;
    float totalTime = 0.0f;
    time_point lastFrame = clockVariant::now();
    time_point lastSecond = clockVariant::now();
};