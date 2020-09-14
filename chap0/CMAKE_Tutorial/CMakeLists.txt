# <---CMake tutorial--->

# <- File Mangement ->
# src: source code
# ext: third-party package and header file

# Define minimum version of CMake
cmake_minimum_required(VERSION 3.0)

# Set the project name
project(cmakeTutorial)

# ADD_EXECUTABLE(<name> [source1] [source2 ...])
# Use source code to generate executable file
#add_executable(cmake_test src/main.cpp)

# AUX_SOURCE_DIRECTORY(dir VARIABLE)
# Detect every source code in a dirctory and store as a variable
aux_source_directory(src SRC_LIST)
add_executable(cmake_test ${SRC_LIST})

# ADD_LIBRARY(<name> [STATIC | SHARED | MODULE] [source1] [source2 ...])
# use source code to generate library


# Set definition in CMake
add_definitions(-DENABLE_DEBUG)

# Enable adding tests
enable_testing()

# ADD_TEST(testname Exename arg1 arg2 ...)
add_test(test ./cmake_test)