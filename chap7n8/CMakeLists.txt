cmake_minimum_required(VERSION 3.10)
project(chap7n8)

set( CMAKE_CXX_FLAG "-std=c++11")

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package( Sophus REQUIRED)
include_directories(${SOPHUS_INCLUDE_DIRS})

include_directories("/usr/include/eigen3" )

add_executable( orb_cv orb_cv.cpp)
target_link_libraries( orb_cv ${OpenCV_LIBS} )

add_executable( pnp pnp.cpp)
target_link_libraries( pnp ${OpenCV_LIBS} )
