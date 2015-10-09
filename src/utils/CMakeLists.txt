cmake_minimum_required(VERSION 3.2)

link_directories(${OpenCV_LIB_DIR})

include_directories(../lib
    ${OpenCV_INCLUDE_DIRS})


add_library(utils
    RF_Utils.cpp)

target_link_libraries(utils ${OpenCV_LIBS})


add_executable(RF_Utils RF_Utils.cpp)

target_link_libraries(RF_Utils utils librf  ${OpenCV_LIBS})

