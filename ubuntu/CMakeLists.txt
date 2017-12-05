cmake_minimum_required(VERSION 2.9)
project(MTCNN_Accelerate-Onet)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV)

find_package(Caffe REQUIRED)
#message(FATAL_ERROR ${Caffe_INCLUDE_DIRS})
include_directories(${Caffe_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp mtcnn.cpp mtcnn.h)
add_executable(MTCNN_Accelerate-Onet ${SOURCE_FILES})

target_link_libraries(MTCNN_Accelerate-Onet ${OpenCV_LIBS} )
target_link_libraries(MTCNN_Accelerate-Onet ${Caffe_LIBRARIES})
