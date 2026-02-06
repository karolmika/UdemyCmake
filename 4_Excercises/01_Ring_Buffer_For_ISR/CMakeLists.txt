cmake_minimum_required(VERSION 3.22)

project(CppProjectTemplate VERSION 1.0.0 LANGUAGES C)

set(EXECUTABLE_NAME RunRingBufferProg)
set(LIBRARY_NAME RingBufferLib)

add_library(${LIBRARY_NAME} ring_buffer.c)

add_executable(${EXECUTABLE_NAME} main.c)

target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_NAME})
