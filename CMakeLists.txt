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
  Csv STATIC
  lib/Csv/Csv.cpp
)

add_library(
  Visualizer STATIC
  lib/Visualizer/Visualizer.cpp
  lib/Visualizer/BarChart.cpp
)

link_libraries(
  Csv
  Visualizer
)

add_executable(licznik src/main.cpp)

target_link_libraries(
  Csv
  Visualizer
)

add_executable(
  test_all
  test/test_main.cpp
  test/test_csv.cpp
)




set(CMAKE_CXX_STANDARD 17)

add_test(NAME licznik COMMAND licznik)
add_test(NAME test_all COMMAND test_all)

target_link_libraries(
  Csv
  Visualizer
)
