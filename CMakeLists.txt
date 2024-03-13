cmake_minimum_required(VERSION 3.12)

# Name project
SET(ProjectName robot_stuff)

# Set any variables required for importing libraries
SET(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeRTOS-Kernel)

# Import those libraries
include(pico_sdk_import.cmake)
include(example_auto_set_url.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Define project
project(${ProjectName})

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()


# Add subdirectories
# Kinda self Explanatory ngl
add_subdirectory(src)
add_subdirectory(mpu)

# When adding more subdirectories, copy a previous folder and change CMakeList.txt with new project name


# if you have anything in "lib" folder then uncomment below - remember to add a CMakeLists.txt
# file to the "lib" directory
#add_subdirectory(lib)