# CHANge "main" TO DESIRED PROJECT NAME

add_executable(main
    # Change to .c file
    main.c
)

target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(main 
    # Add needed pico libraries
    pico_stdlib 
    hardware_pwm
    FreeRTOS-Kernel-Heap4 
    pico_binary_info
    hardware_i2c
    )

pico_add_extra_outputs(main)

# Enable USB compatibility
pico_enable_stdio_usb(main 1)

# Enable UART output
pico_enable_stdio_uart(main 1)