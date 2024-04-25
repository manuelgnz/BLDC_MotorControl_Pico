cmake_minimum_required(VERSION 3.21)

include(pico_sdk_import.cmake)

project(BLDC_MotorControl)

pico_sdk_init()

add_executable(bldcMC
                src/main.c
                src/system.c
)

target_link_libraries(bldcMC pico_stdlib)

target_include_directories(bldcMC PRIVATE ./include)

pico_add_extra_outputs(bldcMC)
