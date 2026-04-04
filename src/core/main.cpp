#include <iostream>
#include <rendering/window.h>

//-----Settings-----
static const int width = 1920;
static const int height = 1080;

int main() {
    try {
        Window window(width, height, "Hello World");

        while (!window.shouldClose()) {
            window.handleEvents();
        }
    } catch(std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}