#include <chrono>

using clockVariant = std::chrono::high_resolution_clock;
using time_point = clockVariant::time_point;
using duration = std::chrono::duration<float>;

class Time {
    public:
        static void update();

        static float getDt();
        static int getFPS();
        static float getTotal();

    private:
        inline static int fps = 0;
        inline static int frames = 0;

        inline static float dt = 0.0f;
        inline static float totalTime = 0.0f;
        inline static time_point lastFrame = clockVariant::now();
        inline static time_point lastSecond = clockVariant::now();
};