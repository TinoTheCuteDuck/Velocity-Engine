#include "core/engineTime.hpp"

void EngineTime::update() {
    frames += 1;

    const time_point now = clockVariant::now();

    const duration dtDuration = now - lastFrame;
    lastFrame = now;

    dt = dtDuration.count();
    totalTime += dt;

    const duration fpsDuration = now - lastSecond;

    if (fpsDuration.count() >= 1.0f) {
        fps = frames;
        frames = 0;
        lastSecond = now;
    }
}

float EngineTime::getDt() const {
    return dt;
}

int EngineTime::getFPS() const {
    return fps;
}

float EngineTime::getTotal() const {
    return totalTime;
}