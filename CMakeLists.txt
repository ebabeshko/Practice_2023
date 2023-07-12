cmake_minimum_required(VERSION 3.26.4)
project(DatabaseManager)

# Встановлення налаштувань компілятора та стандарту
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

# Додайте шляхи до джерел файлів вашого проекту
set(SOURCES
    main.c
    module.c
    module.h
)

# Додайте бібліотеки, якщо вони потрібні
# find_package(<package_name> REQUIRED)

# Встановлення шляху для збірки виконуваного файлу
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Додайте ваші директиви збірки
add_executable(${PROJECT_NAME} ${SOURCES})

# Підключення Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Додавання тестів
set(TEST_SOURCES
    test/test_1.cpp
    # Додайте інші файли з тестами
)

# Створення цільового виконуваного файлу для модульних тестів
add_executable(UnitTests ${TEST_SOURCES})

# Підключення бібліотеки Google Test та потрібних залежностей
target_link_libraries(UnitTests ${GTEST_BOTH_LIBRARIES})

# Додавання виклику тестів під час збірки
enable_testing()
add_test(NAME UnitTests COMMAND UnitTests)
