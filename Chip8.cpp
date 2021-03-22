//
// Created by batzi on 21.03.2021.
//

#include "Chip8.h"

#include <fstream>

const uint32_t START_ADDRESS = 0x200;
const uint32_t FONTSET_SIZE = 80;

//TODO: Change it to std::array
uint8_t fontset[FONTSET_SIZE] = {
                0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                0x20, 0x60, 0x20, 0x20, 0x70, // 1
                0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

void Chip8::LoadROM(std::string_view filename) {
    std::ifstream file(std::string(filename), std::ios::binary | std::ios::ate);

    if(file.is_open()) {
        std::streampos  size{file.tellg()};
        char* buffer = new char[size]; //TODO: Change to vector

        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        for(long i{0}; i < size; ++i) {
            memory[START_ADDRESS + i] = buffer[i];
        }

        delete[] buffer;
    }
    else {
        //TODO: Make Log!
    }
}

Chip8::Chip8(): pc(START_ADDRESS), randomEngine(std::chrono::system_clock::now().time_since_epoch().count()) {
    //Load fonts into memory.
    for(uint32_t i{0}; i < FONTSET_SIZE; ++i) {
        memory[FONTSET_SIZE + i] = fontset[i];
    }

    //Initialize RNG
    randomByte = std::uniform_int_distribution<unsigned short>(0, 255U);
}

void Chip8::OP_00E0() {
    memset(video, 0, sizeof video);
}

void Chip8::OP_00EE() {
    --sp;
    pc = stack[sp];
}

void Chip8::OP_1nnn() {
    uint16_t address = opcode & 0x0FFFu;
    pc = address;
}

void Chip8::OP_2nnn() {
    uint16_t address = opcode & 0x0FFFu;

    stack[sp] = pc;
    ++sp;
    pc = address;
}
