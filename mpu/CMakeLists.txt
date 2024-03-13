add_executable(mpu
    main.c
)

target_include_directories(mpu PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(mpu 
    pico_stdlib 
    hardware_pwm
    FreeRTOS-Kernel-Heap4 
    pico_binary_info
    hardware_i2c
    )

pico_add_extra_outputs(mpu)

# Enable USB compatibility
pico_enable_stdio_usb(mpu 1)

# Enable UART output
pico_enable_stdio_uart(mpu 1)
