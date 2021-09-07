###############################################################################
# Top level CMakeList for building the EVT APM source code
###############################################################################
cmake_minimum_required(VERSION 3.15)

set(EVT_CORE_DIR      ${CMAKE_SOURCE_DIR}/libs/EVT-core)

# Link to the EVT-core library
add_subdirectory(libs/EVT-core/)

include(CMakeDependentOption)
include(${EVT_CORE_DIR}/cmake/evt-core_compiler.cmake)
include(${EVT_CORE_DIR}/cmake/evt-core_install.cmake)

###############################################################################
# Project Setup
###############################################################################
project(rampup
        VERSION 0.0.1
        LANGUAGES CXX C
)

# Add sources

###############################################################################
# Handle dependencies
###############################################################################

# TODO: This should be set by the user of this library
add_compile_definitions(STM32F302x8)

add_definitions(-DUSE_HAL_LIBRARY)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
)

# Make the main executable have an ".elf" suffix
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}"
    SUFFIX ".elf"
)

# Generate a map file
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
                            -Wl,-Map=${PROJECT_NAME}.map")
set(HEX_FILE "${PROJECT_NAME}.hex")
set(BIN_FILE "${PROJECT_NAME}.bin")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}> ${HEX_FILE}
COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}> ${BIN_FILE}
COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")

# Link the EVT-core library
target_link_libraries(${PROJECT_NAME} PUBLIC EVT)
