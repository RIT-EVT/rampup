include(${EVT_CORE_DIR}/cmake/evt-core_build.cmake)

project(phase5)
cmake_minimum_required(VERSION 3.15)

make_exe(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC ${BOARD_LIB_NAME})
