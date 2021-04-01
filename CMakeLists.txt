cmake_minimum_required(VERSION 3.17)
project(CHIP_8_Emulator)

set(CMAKE_CXX_STANDARD 20)

# add_executable(CHIP_8_Emulator source/main.cpp source/Chip8.cpp source/Chip8.h source/Platform.cpp source/Platform.h)

set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2-2.0.14/include/")

# Support both 32 and 64 bit builds
set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2-2.0.14/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2-2.0.14/lib/x64/SDL2main.lib")

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(CHIP_8_Emulator source/main.cpp source/Chip8.cpp source/Chip8.h source/Platform.cpp source/Platform.h)
target_link_libraries(CHIP_8_Emulator ${SDL2_LIBRARIES})