cmake_minimum_required(VERSION 3.10)
project(chap5)

set( CMAKE_CXX_FLAG "-std=c++11")

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( imageBasics imageBasics.cpp )

add_executable( orb orb_cv.cpp)

target_link_libraries( imageBasics ${OpenCV_LIBS} )
