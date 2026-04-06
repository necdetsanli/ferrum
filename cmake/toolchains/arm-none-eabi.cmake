# Target os bare-betal (none)
set(CMAKE_SYSTEM_NAME "Generic")

# Target processor
set(CMAKE_SYSTEM_PROCESSOR "arm")

# C compiler
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")

# Assembler
set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")

# Produces .hex and .bin files from .elf file
set(CMAKE_OBJCOPY "arm-none-eabi-objcopy" CACHE INTERNAL "")

# Produces disassembly of binary
set(CMAKE_OBJDUMP "arm-none-eabi-objdump" CACHE INTERNAL "")

# Shows memory usage of binary
set(CMAKE_SIZE "arm-none-eabi-size" CACHE INTERNAL "")

# This is a cross-compile environment, test binaries wont work on host
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Look to host for tools like CMake, Ninja, etc.
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM "NEVER")

# Look to cross-compile sysroot for libraries
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY "ONLY")

# Look to cross-compile sysroot for headers
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE "ONLY")
