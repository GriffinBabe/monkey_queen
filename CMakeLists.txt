cmake_minimum_required(VERSION 3.16)
project(monkey_queen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add new cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

# Enable threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# GTest
find_package(GTest REQUIRED)

include_directories(SYSTEM include)

add_subdirectory(source)
add_subdirectory(test)
