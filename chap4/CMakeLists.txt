# <- File Mangement ->
# src: source code
# ext: third-party package and header file

# Define minimum version of CMake
cmake_minimum_required(VERSION 3.0)

# Set the project name
project(sophus_test)

# Include eigen3
include_directories("/usr/include/eigen3")

# Include sophus
find_package( Sophus REQUIRED )
include_directories(${Sophus_INCLUDE_DIRS} )

# AUX_SOURCE_DIRECTORY(dir VARIABLE)
# Detect every source code in a dirctory and store as a variable
aux_source_directory(src SRC_LIST)
add_executable(sophus_test ${SRC_LIST})