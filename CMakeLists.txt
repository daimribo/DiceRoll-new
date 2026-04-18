cmake_minimum_required(VERSION 3.28)

project(DiceRoll)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_executable(DiceRoll 
    src/main.cpp
    src/character.cpp)

add_executable(DiceRollTests 
    test/test.cpp)

target_sources(DiceRoll
    PRIVATE
        src/main.cpp
    FILE_SET CXX_MODULES
        FILES
            src/character.cpp)

target_sources(DiceRollTests
    PRIVATE
        test/test.cpp
    FILE_SET CXX_MODULES
        FILES
            src/character.cpp)

target_link_libraries(DiceRollTests PRIVATE 
    GTest::gtest 
    GTest::gtest_main 
    GTest::gmock 
    GTest::gmock_main)

target_link_libraries(DiceRoll PRIVATE 
    SDL3::SDL3 
    SDL3_image::SDL3_image)

add_test(AllTestsInMain main)