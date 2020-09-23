cmake_minimum_required(VERSION 3.17)
project(test_1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES, exp_1.cpp )
set(OpenCV_DIR D:\\Opencv_4.3.0\\opencv\\build)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(test_1  exp_2.cpp)
target_link_libraries(test_1 ${OpenCV_LIBS})