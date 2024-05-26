add_executable(motors
    uppies.cpp
)

target_include_directories(motors PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(motors 
    pico_stdlib
    hardware_pwm
    FreeRTOS-Kernel-Heap4 
    pico_binary_info
    hardware_i2c
    hardware_adc
    )

pico_add_extra_outputs(motors)

# Enable USB compatibility
pico_enable_stdio_usb(motors 1)

# Enable UART output
pico_enable_stdio_uart(motors 1)
