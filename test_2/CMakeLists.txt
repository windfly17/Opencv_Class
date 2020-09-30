cmake_minimum_required(VERSION 3.17)
project(test_2)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES, histgram.cpp )
set(OpenCV_DIR D:\\Opencv_4.3.0\\opencv\\build)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(test_2  histgram.cpp)
target_link_libraries(test_2 ${OpenCV_LIBS})