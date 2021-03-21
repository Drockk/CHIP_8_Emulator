//
// Created by batzi on 21.03.2021.
//

#ifndef CHIP_8_EMULATOR_CHIP8_H
#define CHIP_8_EMULATOR_CHIP8_H

#include <cstdint>
#include <string>

class Chip8 {
public:
    uint8_t registers[16]{};
    uint8_t memory[4096]{};
    uint16_t index{};
    uint16_t pc{};
    uint8_t sp{};
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    uint8_t keypad[16]{};
    uint32_t video[64 * 32]{};
    uint16_t opcode;

    Chip8();

    void LoadROM(std::string_view filename);
};


#endif //CHIP_8_EMULATOR_CHIP8_H
