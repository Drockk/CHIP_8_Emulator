#include <chrono>
#include <iostream>

#include "Platform.h"
#include "Chip8.h"

int main(int argc, char** argv) {
    if(argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
        std::exit(EXIT_FAILURE);
    }

    auto videoScale = std::stoi(argv[1]);
    auto cycleDelay = std::stoi(argv[2]);
    char const* romFilename = argv[3];

    Platform platform("CHIP-8 Emulator", VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);

    Chip8 chip8;
    chip8.loadRom(romFilename);

    uint32_t videoPitch = sizeof chip8.getVideoMemory()[0] * VIDEO_WIDTH;

    auto lastCycleTime = std::chrono::high_resolution_clock::now();
    auto quit{false};

    while(!quit) {
        quit = platform.ProcessInput(chip8.getKeypad());

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        if(dt > cycleDelay) {
            lastCycleTime = currentTime;

            chip8.cycle();

            platform.Update(chip8.getVideoMemory(), videoPitch);
        }
    }

    return 0;
}
