project(SktTrainer)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(libskt)
add_subdirectory(Qt5app)

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

