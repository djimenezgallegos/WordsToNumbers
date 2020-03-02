set(BIN_NAME ${CMAKE_PROJECT_NAME})
set(SOURCES varTemplate.h StringParser.cpp StringParser.h main.cpp)

add_executable(${BIN_NAME} ${SOURCES})
add_library(${BIN_NAME}_lib STATIC ${SOURCES})