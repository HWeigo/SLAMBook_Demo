cmake_minimum_required(VERSION 3.10)
project(chap12)

enable_testing()

set( CMAKE_CXX_FLAG "-std=c++11")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


add_executable( reconstruction main.cpp SGM.cpp )
target_link_libraries( reconstruction ${OpenCV_LIBS})

# add_test(test ./defectsDetection ../ori.jpg)


# add_executable( orb orb_cv.cpp)


