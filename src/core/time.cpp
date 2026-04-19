#include <time.hpp>

void Time::update() {
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

float Time::getDt() {
    return dt;
}

int Time::getFPS() {
    return fps;
}

float Time::getTotal() {
    return totalTime;
}