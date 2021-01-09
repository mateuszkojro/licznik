cmake_minimum_required(VERSION 3.13)

message("________ SETUP ________")

project(licznik VERSION 1.0.0)
include_directories(
  src/
  inc/
  lib/Csv
  lib/Visualizer
  /usr/include
)

enable_testing()

set(CMAKE_CXX_FLAGS "-Wpedantic -g -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 arch=native")

#add_compile_definitions(DEBUG)

add_library(
  Csv SHARED
  lib/Csv/Csv.cpp
)

add_library(
  Visualizer SHARED
  lib/Visualizer/Visualizer.cpp
)

add_executable(licznik src/main.cpp)

set(CMAKE_CXX_STANDARD 17)

add_test(NAME licznik COMMAND licznik)
target_link_libraries(
  Csv
  Visualizer
)
