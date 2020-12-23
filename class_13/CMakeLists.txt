cmake_minimum_required(VERSION 3.17)
project(class_13)

set(CMAKE_CXX_STANDARD 14)

add_executable(class_13 hog.cpp)

set(OpenCV_DIR D:\\Opencv_4.3.0\\opencv\\build)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(class_13 ${OpenCV_LIBS})