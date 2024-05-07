cmake_minimum_required(VERSION 3.21)

include(pico_sdk_import.cmake)

project(BLDC_MotorControl)

pico_sdk_init()

add_executable(bldcMC
                src/main.c
                src/system.c
                src/ifaces/board.c
                src/ifaces/foc.c
                src/console/debug.c
                src/utils/sysTime.c
)

target_link_libraries(bldcMC pico_stdlib pico_stdio hardware_pwm hardware_clocks hardware_adc) # pull in common dependencies and additional pwm hardware support

target_include_directories(bldcMC PRIVATE
                ./include
                ./include/ifaces
                ./include/utils
                ./include/console
)

pico_add_extra_outputs(bldcMC)
