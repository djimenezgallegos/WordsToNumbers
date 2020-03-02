cmake_minimum_required(VERSION 3.10)

# set the project name
project(wordsToNumbers VERSION 1.0.0)

#this is useful for the test to be able to read src files
include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)