cmake_minimum_required(VERSION 3.17)
project(class_7)

set(CMAKE_CXX_STANDARD 14)
set(OpenCV_DIR D:\\Opencv_4.3.0\\opencv\\build)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(class_7 houghLines_1.cpp)
target_link_libraries(class_7 ${OpenCV_LIBS})