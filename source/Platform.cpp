//
// Created by batzi on 01.04.2021.
//

#include "Platform.h"
enum InternalKeys {
    C8_x = 0,
    C8_1 = 1,
    C8_2 = 2,
    C8_3 = 3,
    C8_q = 4,
    C8_w = 5,
    C8_e = 6,
    C8_a = 7,
    C8_s = 8,
    C8_d = 9,
    C8_c = 10,
    C8_z = 11,
    C8_4 = 12,
    C8_r = 13,
    C8_f = 14,
    C8_v = 15,
    C8_ESCAPE = 33
};

uint32_t getInternalKey(const SDL_Event& event) {
    switch(event.key.keysym.sym) {
        case SDLK_ESCAPE:
            return InternalKeys::C8_ESCAPE;
        case SDLK_x:
            return InternalKeys::C8_x;
        case SDLK_1:
            return C8_1;
        case SDLK_2:
            return C8_2;
        case SDLK_3:
            return C8_3;
        case SDLK_q:
            return C8_q;
        case SDLK_w:
            return C8_w;
        case SDLK_e:
            return C8_e;
        case SDLK_a:
            return C8_a;
        case SDLK_s:
            return C8_s;
        case SDLK_d:
            return C8_d;
        case SDLK_c:
            return C8_c;
        case SDLK_z:
            return C8_z;
        case SDLK_4:
            return C8_4;
        case SDLK_r:
            return C8_r;
        case SDLK_f:
            return C8_f;
        case SDLK_v:
            return C8_v;
    }

    return -1;
}

Platform::Platform(const char *title, int windowWidth, int windowHeight, int textureWidth, int textureHeight) {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
}

Platform::~Platform() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Platform::Update(const void *buffer, int pitch) {
    SDL_UpdateTexture(texture, nullptr, buffer, pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

bool Platform::ProcessInput(uint8_t *keys) {
    auto quit{false};

    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN: {
                onKeyDown(keys, event, quit);
                break;
            }
            case SDL_KEYUP: {
                onKeyUp(keys, event, quit);
                break;
            }
        }
    }
    return quit;
}

void Platform::onKeyDown(uint8_t* keys, const SDL_Event &event, bool &quit) {
    auto key = getInternalKey(event);

    if(key == InternalKeys::C8_ESCAPE)
        quit = true;
    else
        keys[key] = 1;
}

void Platform::onKeyUp(uint8_t *keys, const SDL_Event &event, bool &quit) {
    auto key = getInternalKey(event);
    keys[key] = 0;
}
