add_executable(${ProjectName}
    main.c
)

target_include_directories(${ProjectName} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${ProjectName} 
    pico_stdlib 
    hardware_pwm
    FreeRTOS-Kernel-Heap4 
    pico_binary_info
    hardware_i2c
    )

pico_add_extra_outputs(${ProjectName})

# Enable UART output
pico_enable_stdio_uart(${ProjectName} 1)

pico_add_extra_outputs(${ProjectName})