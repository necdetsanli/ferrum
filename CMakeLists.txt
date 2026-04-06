# Minimum required version of CMake
cmake_minimum_required(VERSION 4.0.0)

# Project information
project("Ferrum" C ASM)

# MCU Specific Compiler Flags
if ("${TARGET_MCU}" STREQUAL "stm32f411ce")
    set(CHIP "STM32F411xx")
    set(FLASH_SIZE 0x80000)
    set(RAM_SIZE 0x20000)
elseif ("${TARGET_MCU}" STREQUAL "stm32f401ce")
    set(CHIP "STM32F401xx")
    set(FLASH_SIZE 0x40000)
    set(RAM_SIZE 0x10000)
else ()
    message(FATAL_ERROR "Unsupported TARGET_MCU: '${TARGET_MCU}'. Supported: stm32f411ce, stm32f401ce")
endif()

# Set MCU definition macro for compiler
add_compile_definitions(${CHIP})

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_options(
        -Og
        -g3
    )
    add_compile_definitions(DEBUG)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_compile_options(
        -Os
    )
    add_link_options(
        -flto
    )
    add_compile_definitions(NDEBUG)
else()
     message(FATAL_ERROR "Unsupported BUILD_TYPE: '${CMAKE_BUILD_TYPE}'. Supported: Debug, Release")
endif()

# Set hardware flags
add_compile_options(
    -mcpu=cortex-m4 # Target CPU core
    -mthumb # Instruction set
    -mfloat-abi=hard # Use FPU for floating point operations
    -mfpu=fpv4-sp-d16 # FPU type of Cortex-M4 (single precision, 16 double-word register)
)

# Generates .ld file for target MCU
configure_file("${CMAKE_SOURCE_DIR}/cmake/linker/stm32f4.ld.in" "${CMAKE_BINARY_DIR}/${TARGET_MCU}.ld")

# Set warning flags for compiler
add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wshadow # Warning for name shadowing
    -Wdouble-promotion # Warns if float promotes to double
    -Wformat-truncation # Warns if there is a risk of buffer overflow
    -Wconversion # Warns if there is a implicit type conversion
    -Wcast-align # Warns if there is a pointer cast which can cause alignment issue
)

# Optimization and section flags
add_compile_options(
    -ffunction-sections # Puts every function to a different section
    -fdata-sections # Puts every global variable to a different section
)

# Linker flags
add_link_options(
    -mcpu=cortex-m4
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -nostdlib # Dont link standard C library
    # -specs=nosys.specs # Make system calls stub
    -Wl,--gc-sections # Throw unused sections
    -Wl,--Map=${PROJECT_NAME}.map
    -T="${CMAKE_BINARY_DIR}/${TARGET_MCU}.ld"
)
