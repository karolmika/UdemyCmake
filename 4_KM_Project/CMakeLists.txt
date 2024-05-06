# 0.) Crate source and CMakeLists.txt
# 1.) mkdir build
# 2.) cd build
# 3.) cmake .. - Generating the Build Files / Configure the Project
# 4.) cmake --build .
# 5.) ./Executable
cmake_minimum_required(VERSION 3.22)

project(CppProjectTemplate VERSION 1.0.0 LANGUAGES C CXX)

# overwriting some default CMake variables
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

option(ENABLE_TESTING "Enable a Unit Testing Build" ON)

option(ENABLE_WARNINGS "Enable warnings" ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable warnings as errors" OFF)

option(ENABLE_SANITIZE_ADDR "Enable address sanitizer" ON)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitizer" ON)

option(ENABLE_LTO "Enable LTO" ON)

# setting custom Variables
set(LIBRARY_NAME "Library")
set(EXECUTABLE_NAME "Executable")

# optional parameters (True/False)
# option(COMPILE_EXECUTABLE "Whether to compile the executable " ON)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(AddGitSubmodule)
include(FetchContent)
include(Docs)

if(ENABLE_WARNINGS)
    include(Warnings)
endif()

if(ENABLE_SANITIZE_ADDR OR ENABLE_SANITIZE_UNDEF)
    include(Sanitizer)
    add_sanitizer_flags(ENABLE_SANITIZE_ADDR ENABLE_SANITIZE_UNDEF)
endif()

if(ENABLE_LTO)
    include(LTO)
endif()

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.2
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG 9.1.0
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG v1.11.0
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts
    GIT_TAG v3.0.0
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(cxxopts)

if(ENABLE_TESTING)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG v3.5.3
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif()

# add_git_submodule(external/json)

add_subdirectory(configured)
add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(app)

if(ENABLE_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

# if (COMPILE_EXECUTABLE)
#     add_subdirectory(app)
# else()
#     message("Without exe. compiling")
# endif()
