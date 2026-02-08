cmake_minimum_required(VERSION 3.22)

project(CppProjectTemplate VERSION 1.0.0 LANGUAGES C)

set(EXECUTABLE_NAME RunProtocolParserProgam)
set(LIBRARY_NAME ProtocolParserLib)

add_library(${LIBRARY_NAME} parser.c)

add_executable(${EXECUTABLE_NAME} main.c)

target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_NAME})
