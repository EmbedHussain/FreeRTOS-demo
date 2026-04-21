cmake_minimum_required(VERSION 3.16)
project(freertos_simple C)

set(CMAKE_C_STANDARD 11)

include(FetchContent)

FetchContent_Declare(
  freertos_kernel
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG main
)

FetchContent_MakeAvailable(freertos_kernel)

add_executable(demo main.c)

target_include_directories(demo PRIVATE ${freertos_kernel_SOURCE_DIR}/include)

target_sources(demo PRIVATE
    ${freertos_kernel_SOURCE_DIR}/portable/ThirdParty/GCC/Posix/port.c
    ${freertos_kernel_SOURCE_DIR}/portable/MemMang/heap_4.c
)

target_link_libraries(demo pthread)
