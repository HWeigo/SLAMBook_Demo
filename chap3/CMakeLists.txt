cmake_minimum_required(VERSION 3.10)

# Set the project name
project(eigen_test)

include_directories("/usr/include/eigen3")

# AUX_SOURCE_DIRECTORY(dir VARIABLE)
# Detect every source code in a dirctory and store as a variable
aux_source_directory(src SRC_LIST)
add_executable(eigen_test ${SRC_LIST})