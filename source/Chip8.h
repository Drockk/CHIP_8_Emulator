//
// Created by batzi on 21.03.2021.
//

#ifndef CHIP_8_EMULATOR_CHIP8_H
#define CHIP_8_EMULATOR_CHIP8_H

#include <cstdint>
#include <string>
#include <chrono>
#include <random>
#include <array>

constexpr uint32_t VIDEO_WIDTH { 64 };
constexpr uint32_t VIDEO_HEIGHT { 32 };
constexpr uint32_t VIDEO_MEMORY { VIDEO_WIDTH * VIDEO_HEIGHT };
constexpr uint32_t REGISTER_COUNT { 16 };
constexpr uint32_t KEY_COUNT { 16 };
constexpr uint32_t STACK_LEVELS { 16 };
constexpr uint32_t MEMORY_SIZE { 4096 };

class Chip8 {
public:
    Chip8();

    void loadRom(std::string_view filename);
    void cycle();

    uint8_t* getKeypad();
    uint32_t* getVideoMemory();
private:
    void OP_00E0();
    void OP_00EE();
    void OP_1nnn();
    void OP_2nnn();
    void OP_3xkk();
    void OP_4xkk();
    void OP_5xy0();
    void OP_6xkk();
    void OP_7xkk();
    void OP_8xy0();
    void OP_8xy1();
    void OP_8xy2();
    void OP_8xy3();
    void OP_8xy4();
    void OP_8xy5();
    void OP_8xy6();
    void OP_8xy7();
    void OP_8xyE();
    void OP_9xy0();
    void OP_Annn();
    void OP_Bnnn();
    void OP_Cxkk();
    void OP_Dxyn();
    void OP_Ex9E();
    void OP_ExA1();
    void OP_Fx07();
    void OP_Fx0A();
    void OP_Fx15();
    void OP_Fx18();
    void OP_Fx1E();
    void OP_Fx29();
    void OP_Fx33();
    void OP_Fx55();
    void OP_Fx65();
    void OP_NULL();

    void Table0();
    void Table8();
    void TableE();
    void TableF();

    std::array<uint32_t, VIDEO_MEMORY> video{};
    std::array<uint16_t, STACK_LEVELS> stack{};
    uint16_t index{};
    uint16_t pc{};
    uint16_t opcode{};
    std::array<uint8_t, MEMORY_SIZE> memory{};
    std::array<uint8_t, REGISTER_COUNT> registers{};
    std::array<uint8_t, KEY_COUNT> keypad{};
    uint8_t sp{};
    uint8_t delayTimer{};
    uint8_t soundTimer{};

    std::default_random_engine randomEngine{};
    std::uniform_int_distribution<unsigned short> randomByte{};

    typedef void (Chip8::*Chip8Func)();
    Chip8Func table[0xF + 1]{&Chip8::OP_NULL};
    Chip8Func table0[0xE + 1]{&Chip8::OP_NULL};
    Chip8Func table8[0xE + 1]{&Chip8::OP_NULL};
    Chip8Func tableE[0xE + 1]{&Chip8::OP_NULL};
    Chip8Func tableF[0x65 + 1]{&Chip8::OP_NULL};
};


#endif //CHIP_8_EMULATOR_CHIP8_H
