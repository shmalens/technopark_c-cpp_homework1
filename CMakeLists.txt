cmake_minimum_required(VERSION 3.8)
project(HomeWork1)

# Создаем имя таргета сборки самой программы
set(TARGET compilation)

# Выставляем флаги компилятора и проч инфу для компилятора
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O0 -ggdb3 -Wextra -Werror")

set(PROJECT_SOURCE_DIR project)

# Создаем таргет, указываем для него мейн
add_executable(${TARGET} ${PROJECT_SOURCE_DIR}/main.c)
# Подключаем к нему хедеры
include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC ${PROJECT_SOURCE_DIR}/src)

# Теперь делаем статическую библиотеку со всеми сорсами
add_library(hw_lib STATIC ${SRC}/compilation.c  
                          ${SRC}/composition.c  
                          ${SRC}/dataloader.c 
                          ${SRC}/playlist.c)

# Подключаем библиотеку к цели
target_link_libraries(${TARGET} hw_lib)

# Тут происходит конфигурация тетов, 
# они подтягиваются с гита, для этого нужен CMakeLists.txt.in
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

# Включаем тестирование для этого каталога
enable_testing()

set(TEST_NAME tests_gtest)

# Создаем таргет на тесты
add_executable(tests_gtest test/${TEST_NAME}.cpp)
# Теперь подключаем гуглотесты к их таргету
target_link_libraries(${TEST_NAME} gtest_main)
# Теперь подключаем тестируемые функции к таргету тестов
target_link_libraries(${TEST_NAME} hw_lib)
# Создаем тест
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})