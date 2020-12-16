cmake_minimum_required(VERSION 3.10)
project(chap5)

enable_testing()

set( CMAKE_CXX_FLAG "-std=c++11")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_definitions(-DDEBUG_IMAGESAVE)

add_executable( imageBasics imageBasics.cpp )
target_link_libraries( imageBasics ${OpenCV_LIBS} )

add_executable( defectsDetection main.cpp )
target_link_libraries( defectsDetection ${OpenCV_LIBS})

add_test(test ./defectsDetection ../ori.jpg)


# add_executable( orb orb_cv.cpp)


