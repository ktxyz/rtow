//
// Created by Kamil Tokarski on 26/07/2024.
//

#include <fstream>
#include <iostream>

const char* PPM_HEADER = "P3\n";
constexpr double PPM_VALUE = 255.99;

int main() {
    auto file = std::ofstream("output.ppm");
    constexpr int WIDTH = 1024;
    constexpr int HEIGHT = WIDTH;

    file << PPM_HEADER << WIDTH << " " << HEIGHT << "\n255\n";
    for (auto y = 0; y < HEIGHT; ++y) {
        std::cerr << "Scanlines remaining: " << (HEIGHT - y) << "\n";
        for(auto x = 0; x < WIDTH; ++x) {
            auto r = static_cast<double>(x) / (WIDTH - 1);
            auto g = static_cast<double>(y) / (HEIGHT - 1);
            auto b = 0.0;

            file << static_cast<int>(PPM_VALUE * r) << " " << static_cast<int>(PPM_VALUE * g) << " " << static_cast<int>(PPM_VALUE * b) << "\n";
        }
    }

    std::cerr << "Finished." << "\n";

    return 0;
}
