# compilation in release mode
# cmake -DCMAKE_BUILD_TYPE=Release ..

# add information about source code
# cmake -DCMAKE_C_FLAGS=-g ..

# gdb ./main
# r / run
# bt / backtrace
# f / frame
# print var

cmake_minimum_required(VERSION 3.10)

project(PPD2 VERSION 1.0)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wpedantic -Wextra")

include_directories(PUBLIC include)

# shared object files
set(OBJECT_FILES
    src/bmp_file.c
    src/mosaic_filter.c
    src/utils.c)

add_executable(test01_load tests/test_load.c ${OBJECT_FILES})
add_executable(test02_copy tests/test_copy.c ${OBJECT_FILES})
add_executable(test03_create tests/test_create.c ${OBJECT_FILES})
add_executable(test04_reduction tests/test_reduction.c ${OBJECT_FILES})
add_executable(test05_tile tests/test_tile.c ${OBJECT_FILES})
