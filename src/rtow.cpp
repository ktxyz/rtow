//
// Created by Kamil Tokarski on 26/07/2024.
//

#include <fstream>
#include <iostream>

#include "color.h"


const char* PPM_HEADER = "P3\n";

int main() {
    auto file = std::ofstream("output.ppm");
    constexpr int WIDTH = 1024;
    constexpr int HEIGHT = WIDTH;

    file << PPM_HEADER << WIDTH << " " << HEIGHT << "\n255\n";
    for (auto y = 0; y < HEIGHT; ++y) {
        std::cerr << "Scanlines remaining: " << (HEIGHT - y) << "\n";
        for(auto x = 0; x < WIDTH; ++x) {
            auto pixel = Color(
                static_cast<double>(x) / (WIDTH - 1),
                static_cast<double>(y) / (HEIGHT - 1),
                0
            );

            file << pixel << "\n";
        }
    }

    std::cerr << "Finished." << "\n";

    return 0;
}
