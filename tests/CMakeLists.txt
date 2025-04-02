cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "UnitTest")
project(${PROJECT_NAME} LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} blockingqueue Threads::Threads gtest)