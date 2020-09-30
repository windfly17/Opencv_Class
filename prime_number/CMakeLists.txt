cmake_minimum_required(VERSION 3.17)
project(prime_number)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES, main.cpp)
set(OpenCV_DIR D:\\Opencv_4.3.0\\opencv\\build)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(prime_number main.cpp)
target_link_libraries(prime_number ${OpenCV_LIBS})