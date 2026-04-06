# @file arm-none-eabi-gcc.cmake
# @brief Toolchain configuration for baremetal ARM GNU cross-compilation.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_SIZE arm-none-eabi-size)

set(LPC_CPU_FLAGS "-mcpu=cortex-m4 -mthumb" CACHE STRING "Target CPU flags")

set(CMAKE_C_FLAGS_INIT "${LPC_CPU_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "${LPC_CPU_FLAGS}")
set(CMAKE_ASM_FLAGS_INIT "${LPC_CPU_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${LPC_CPU_FLAGS} -Wl,--gc-sections")
