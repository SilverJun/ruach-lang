cmake_minimum_required(VERSION 3.15)
project(ruach_lang)

set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR}/src)

# dependencies
add_subdirectory(lib/Catch2)
include_directories(${PROJECT_SOURCE_DIR}/lib/Catch2/single_include)

# ruach core
file(GLOB_RECURSE RUACH_CORE "${PROJECT_SOURCE_DIR}/src/core/*.cpp" "${PROJECT_SOURCE_DIR}/src/core/*.h")
add_library(ruach_core STATIC ${RUACH_CORE})
add_executable(ruach_core_test ${PROJECT_SOURCE_DIR}/src/tests/RuachCoreTests.cpp)
target_link_libraries(ruach_core_test Catch2::Catch2)
target_link_libraries(ruach_core_test ruach_core)

# ruach interpreter
add_executable(ruach_interpreter main.cpp)
