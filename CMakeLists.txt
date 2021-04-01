cmake_minimum_required(VERSION 3.17)
project(CHIP_8_Emulator)

set(CMAKE_CXX_STANDARD 20)

# add_executable(CHIP_8_Emulator source/main.cpp source/Chip8.cpp source/Chip8.h source/Platform.cpp source/Platform.h)

set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2-2.0.14/include/")

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2-2.0.14/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2-2.0.14/lib/x64/SDL2main.lib")
else ()
    set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2-2.0.14/lib/x86/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2-2.0.14/lib/x86/SDL2main.lib")
endif ()

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(CHIP_8_Emulator source/main.cpp source/Chip8.cpp source/Chip8.h source/Platform.cpp source/Platform.h ${SDL2_LIBRARIES})