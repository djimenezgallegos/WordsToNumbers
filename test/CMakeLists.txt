set(BIN_NAME ${CMAKE_PROJECT_NAME}_test)
set(SOURCES StringParser-test.cpp main.cpp)

add_executable(${BIN_NAME} ${SOURCES})
add_test(${BIN_NAME} COMMAND ${BIN_NAME})
target_link_libraries(${BIN_NAME} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)