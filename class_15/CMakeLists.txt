cmake_minimum_required(VERSION 3.17)
project(class_15)

set(CMAKE_CXX_STANDARD 14)

add_executable(class_15 main.cpp)

set(OpenCV_DIR D:\\Opencv_4.3.0\\opencv\\build)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(class_15 ${OpenCV_LIBS})