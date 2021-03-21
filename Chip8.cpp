//
// Created by batzi on 21.03.2021.
//

#include "Chip8.h"

#include <fstream>

const uint32_t START_ADDRESS = 0x200;

void Chip8::LoadROM(std::string_view filename) {
    std::ifstream file(std::string(filename), std::ios::binary | std::ios::ate);

    if(file.is_open())
    {
        std::streampos  size{file.tellg()};
        char* buffer = new char[size]; //TODO: Change to vector

        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        for(long i{0}; i < size; ++i)
        {
            memory[START_ADDRESS + i] = buffer[i];
        }

        delete[] buffer;
    }
    else
    {
        //TODO: Make Log!
    }
}

Chip8::Chip8(): pc(START_ADDRESS) {

}
