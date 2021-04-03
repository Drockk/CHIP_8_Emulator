//
// Created by batzi on 01.04.2021.
//

#ifndef CHIP_8_EMULATOR_PLATFORM_H
#define CHIP_8_EMULATOR_PLATFORM_H
#include <cstdint>
#include <SDL.h>

class Platform {
public:
    Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
    ~Platform();

    void Update(void const* buffer, int pitch);

    bool ProcessInput(uint8_t* keys);

private:
    SDL_Window* window{};
    SDL_Renderer* renderer{};
    SDL_Texture* texture{};
};


#endif //CHIP_8_EMULATOR_PLATFORM_H
