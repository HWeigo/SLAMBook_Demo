cmake_minimum_required(VERSION 3.10)
project(chap5)

set( CMAKE_CXX_FLAG "-std=c++11")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


find_package(G20 REQUIRED)
include_directories( ${G20_INCLUDE_DIRS})

find_package( Sophus REQUIRED)
include_directories(${SOPHUS_INCLUDE_DIRS})

include_directories("/usr/include/eigen3" )

add_executable( imageBasics imageBasics.cpp )

add_executable( orb orb_cv.cpp)

add_executable( pnp ppn.cpp)

target_link_libraries( imageBasics ${OpenCV_LIBS} )
