# Minimum required version of CMake
cmake_minimum_required(VERSION 4.0.0)

# Project information
project("Ferrum" C ASM)

# MCU Specific Compiler Flags
if ("${TARGET_MCU}" MATCHES "^stm32f4")
    set(MCU_FAMILY_DIR "${CMAKE_SOURCE_DIR}/config/mcu/stm32f4")

    if ("${TARGET_MCU}" STREQUAL "stm32f411ce")
        set(CHIP "STM32F411xE")
        set(FLASH_SIZE 0x80000)
        set(RAM_SIZE 0x20000)
    elseif ("${TARGET_MCU}" STREQUAL "stm32f401ce")
        set(CHIP "STM32F401xC")
        set(FLASH_SIZE 0x40000)
        set(RAM_SIZE 0x10000)
    else ()
        message(FATAL_ERROR "Unsupported STM32F4 MCU: '${TARGET_MCU}'")
    endif()

# elseif ("${TARGET_MCU}" MATCHES "^stm32f1")
#     set(MCU_FAMILY_DIR "${CMAKE_SOURCE_DIR}/config/mcu/stm32f1")
#     ...

else ()
    message(FATAL_ERROR "Unsupported TARGET_MCU: '${TARGET_MCU}'")
endif()

# Set MCU definition macro for compiler
add_compile_definitions("${CHIP}")

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

# Target board selection. Path is relative to config/boards/, without .h. Override at configure time with -DBOARD=<family>/<board>.
set(BOARD "stm32f4/blackpill_f411ce" CACHE STRING "Target board (path under config/boards without .h)")

# Resolve and validate the selected board header, then expose it under a generic name (board.h) so source files stay board-agnostic.
set(BOARD_HEADER_SRC "${CMAKE_SOURCE_DIR}/config/boards/${BOARD}.h")
if(NOT EXISTS "${BOARD_HEADER_SRC}")
    message(FATAL_ERROR "Board header not found: ${BOARD_HEADER_SRC}")
endif()
configure_file("${BOARD_HEADER_SRC}" "${CMAKE_BINARY_DIR}/generated/board.h" COPYONLY)
get_filename_component(BOARD_DIR "${BOARD_HEADER_SRC}" DIRECTORY)


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
    -T ${CMAKE_BINARY_DIR}/${TARGET_MCU}.ld
)

# Build targets
add_executable(
    "${PROJECT_NAME}"
    "${CMAKE_SOURCE_DIR}/examples/01_blinky/main.c"
    "${CMAKE_SOURCE_DIR}/system/stm32f4/startup_stm32f4.c"
    "${CMAKE_SOURCE_DIR}/system/stm32f4/system_stm32f4.c"
)

# Output
set_target_properties("${PROJECT_NAME}" PROPERTIES SUFFIX ".elf")

# Include directories
target_include_directories(
    "${PROJECT_NAME}"
    PRIVATE
    "${CMAKE_SOURCE_DIR}/cmsis/arm"
    "${CMAKE_SOURCE_DIR}/cmsis/st"
    "${CMAKE_SOURCE_DIR}/system/stm32f4"
    "${CMAKE_BINARY_DIR}/generated"
    "${MCU_FAMILY_DIR}"
    "${BOARD_DIR}"
)
