//
// Created by batzi on 21.03.2021.
//

#ifndef CHIP_8_EMULATOR_CHIP8_H
#define CHIP_8_EMULATOR_CHIP8_H

#include <cstdint>
#include <string>
#include <chrono>
#include <random>

class Chip8 {
public:
    uint8_t registers[16]{};
    uint8_t memory[4096]{};
    uint16_t index{};
    uint16_t pc{};
    uint16_t stack[16]{};
    uint8_t sp{};
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    uint8_t keypad[16]{};
    uint32_t video[64 * 32]{};
    uint16_t opcode;

    Chip8();

    void LoadROM(std::string_view filename);
private:
    void OP_00E0();
    void OP_00EE();
    void OP_1nnn();
    void OP_2nnn();
    void OP_3xkk();
    void OP_4xkk();


    std::default_random_engine randomEngine;
    std::uniform_int_distribution<unsigned short> randomByte;
};


#endif //CHIP_8_EMULATOR_CHIP8_H
