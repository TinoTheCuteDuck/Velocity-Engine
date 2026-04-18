#include <engine.hpp>

int main() {
    try {
        Engine engine;
        engine.run();
    } catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}