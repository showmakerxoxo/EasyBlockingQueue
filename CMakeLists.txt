cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "EasyBlockingQueue")
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX)

option(BUILD_EXAMPLE "build example" ON)
option(BUILD_TESTS "build tests" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

set(LIBNAME "blockingqueue")
add_library(${LIBNAME} INTERFACE)
target_include_directories(${LIBNAME}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${LIBNAME} INTERFACE Threads::Threads)

if (BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

if (BUILD_TESTS)
    include_directories(
        googletest/googletest
        googletest/googletest/include
    )
    add_subdirectory(googletest)
    add_subdirectory(tests)
endif()
