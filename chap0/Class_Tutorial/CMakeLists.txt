cmake_minimum_required(VERSION 3.0)

project(ClassTest)

aux_source_directory(src SRC)
add_executable(class_test ${SRC})
