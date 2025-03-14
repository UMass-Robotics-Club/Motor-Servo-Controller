cmake_minimum_required(VERSION 3.13)

    # initialize the SDK based on PICO_SDK_PATH
    # note: this must happen before project()
    include(pico_sdk_import.cmake)

    project(motor_firmware)

    # initialize the Raspberry Pi Pico SDK
    pico_sdk_init()

    file(GLOB SRCS ./src/*.c)
    add_executable(main ${SRCS})

    target_include_directories(main PUBLIC ./include)

    # Add pico_stdlib library which aggregates commonly used features
    target_link_libraries(main pico_stdlib hardware_pwm)

    # create map/bin/hex/uf2 file in addition to ELF.
    pico_add_extra_outputs(main)