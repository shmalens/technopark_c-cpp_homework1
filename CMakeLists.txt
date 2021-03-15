cmake_minimum_required(VERSION 3.8)
project(HomeWork1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -ggdb3")

include_directories(project/include)
include_directories(SYSTEM ${CMAKE_BINARY_DIR}/include)

include(ExternalProject) # Подключает ExternalProject_Add
find_package(Git REQUIRED)

add_library(hw_lib STATIC project/src/compilation.c
        project/src/composition.c
        project/src/dataloader.c
        project/src/playlist.c)

set(TARGET compilation)
add_executable(${TARGET} project/main.c)
target_link_libraries(${TARGET} hw_lib)

option(ENABLE_COVERAGE "Build tests coverage statistic" OFF)
if (ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif ()

option(ENABLE_CPPCHECK "Configure and run cppcheck." OFF) # Makes boolean 'test' available.
if (ENABLE_CPPCHECK)

    list(APPEND CPPCHECK_CMAKE_ARGS
            "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
            )

    ExternalProject_Add(
            cppcheck
            GIT_REPOSITORY https://github.com/danmar/cppcheck.git
            GIT_TAG 1.79
            GIT_SHALLOW 1
            CMAKE_ARGS ${CPPCHECK_CMAKE_ARGS}
            PREFIX ${CMAKE_BINARY_DIR}/external/cppcheck/prefix
            TMP_DIR ${CMAKE_BINARY_DIR}/external/cppcheck/tmp
            STAMP_DIR ${CMAKE_BINARY_DIR}/external/cppcheck/stamp
            DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/external/cppcheck/download
            SOURCE_DIR ${CMAKE_BINARY_DIR}/external/cppcheck/src
            BINARY_DIR ${CMAKE_BINARY_DIR}/external/cppcheck/build
    )

    list(APPEND CPPCHECK_ARGS1
            --enable=all
            --std=c11
            --verbose
            --error-exitcode=1
            --language=c
            --suppress=missingIncludeSystem
            ${CMAKE_SOURCE_DIR}/project/src/*.c
            )

    list(APPEND CPPCHECK_ARGS2
            --enable=all
            --verbose
            --error-exitcode=1
            --language=c++
            ${CMAKE_SOURCE_DIR}/test/*.cpp
            )

    add_custom_target(
            check1
            COMMAND ${CMAKE_BINARY_DIR}/bin/cppcheck ${CPPCHECK_ARGS1}
            COMMENT "running cppcheck"
    )

    add_custom_target(
            check2
            COMMAND ${CMAKE_BINARY_DIR}/bin/cppcheck ${CPPCHECK_ARGS2}
            COMMENT "running cppcheck"
    )

endif ()


## Создаем таргет, указываем для него мейн
#add_executable(${TARGET} project/main.c)
## Подключаем к нему хедеры
#
## Теперь делаем статическую библиотеку со всеми сорсами
#
#
## Подключаем библиотеку к цели
#target_link_libraries(${TARGET} hw_lib)
#
## Тут происходит конфигурация тестов,
## они подтягиваются с гита, для этого нужен CMakeLists.txt.in
#configure_file(CMakeLists.txt.in
#        googletest-download/CMakeLists.txt)
#execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
#execute_process(COMMAND ${CMAKE_COMMAND} --build .
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
#
#add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
#        ${CMAKE_BINARY_DIR}/googletest-build)
#
## Включаем тестирование для этого каталога


option(BUILD_TESTS "Build all tests." OFF) # Makes boolean 'test' available.
if (BUILD_TESTS)
    add_subdirectory(googletest-release-1.10.0)
    include(CTest)

    enable_testing()

    file(GLOB test_source test/composition.cpp test/playlist.cpp test/dataloader.cpp test/compilation.cpp)

    foreach (file ${test_source})
        set(name)
        get_filename_component(name ${file} NAME_WE)
        add_executable("${name}_tests" ${file})
        target_link_libraries("${name}_tests" gtest_main)
        target_link_libraries("${name}_tests" hw_lib)
        add_test(NAME ${name} COMMAND "${name}_tests")
    endforeach ()
endif ()