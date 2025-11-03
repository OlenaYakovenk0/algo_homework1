cmake_minimum_required(VERSION 3.16)
project(v2_tasks LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

include_directories("${CMAKE_SOURCE_DIR}")

# add_executable(test3 task3/test3.cpp)
# target_compile_definitions(test3 PRIVATE PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
add_executable(test2 task2/test2.cpp)
target_compile_definitions(test2 PRIVATE PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
