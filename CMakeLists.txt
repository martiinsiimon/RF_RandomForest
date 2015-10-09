cmake_minimum_required(VERSION 3.2)
project(RF_RandomForest)

find_package(OpenCV REQUIRED)

set(RF_VERSION_MAJOR 0)
set(RF_VERSION_MINOR 1)
set(RF_VERSION_PATCH 0)
set(RF_VERSION ${RF_VERSION_MAJOR}.${RF_VERSION_MINOR}.${RF_VERSION_PATCH})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(src/lib)
add_subdirectory(src/utils)

