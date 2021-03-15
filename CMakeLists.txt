cmake_minimum_required(VERSION 3.8)
project(HomeWork1)

# Создаем имя таргета сборки самой программы
set(TARGET compilation)

# Выставляем флаги компилятора и проч инфу для компилятора
#set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O0 -ggdb3 -Wextra -Werror -Wshadow")
#set(PROJECT_SOURCE_DIR project)
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -ggdb3")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

# Создаем таргет, указываем для него мейн
add_executable(${TARGET} ${PROJECT_SOURCE_DIR}/main.c)
# Подключаем к нему хедеры
include_directories(project/include)

# Теперь делаем статическую библиотеку со всеми сорсами
add_library(hw_lib STATIC project/src/compilation.c
        project/src/composition.c
        project/src/dataloader.c
        project/src/playlist.c)

# Подключаем библиотеку к цели
target_link_libraries(${TARGET} hw_lib)

# Тут происходит конфигурация тетов,
# они подтягиваются с гита, для этого нужен CMakeLists.txt.in
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

# Включаем тестирование для этого каталога
enable_testing()

file(GLOB test_source test/composition.cpp test/playlist.cpp test/dataloader.cpp test/compilation.cpp)

foreach(file ${test_source})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests" ${file})
    target_compile_options("${name}_tests" PUBLIC "--coverage")
    target_link_libraries("${name}_tests" gtest_main)
    target_link_libraries("${name}_tests" hw_lib)
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()