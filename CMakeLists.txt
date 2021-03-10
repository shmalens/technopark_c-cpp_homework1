cmake_minimum_required(VERSION 3.8)
project(HomeWork1)

set(TARGET compilation.out)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O0 -ggdb3 -Wextra -Werror")

add_executable(${TARGET} project/main.c)
include_directories(project/include/)

set(SRC project/src)

add_library(hw_lib STATIC ${SRC}/compilation.c  
                          ${SRC}/composition.c  
                          ${SRC}/dataloader.c 
                          ${SRC}/playlist.c)

target_link_libraries(${TARGET} hw_lib)