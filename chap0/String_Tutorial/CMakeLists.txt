cmake_minimum_required(VERSION 3.0)

project(StringTest)

aux_source_directory(src SRC)
add_executable(string_test ${SRC})

