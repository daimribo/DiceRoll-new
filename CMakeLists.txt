cmake_minimum_required(VERSION 3.28)

project(DiceRoll)

set(CMAKE_CXX_STANDARD 20)

find_package(jsoncpp CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_executable(DiceRoll
    src/main.cpp
)

target_sources(DiceRoll
    PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES
        FILES src/character.cppm
        FILES src/mechanics.cppm
)

add_executable(DiceRollTests
    test/test.cpp
)

target_sources(DiceRollTests
    PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES
        FILES src/character.cppm
)

target_link_libraries(DiceRollTests PRIVATE 
    GTest::gtest 
    GTest::gtest_main
    JsonCpp::JsonCpp)

target_link_libraries(DiceRoll PRIVATE 
    SDL3::SDL3 
    SDL3_image::SDL3_image
    JsonCpp::JsonCpp)

add_test(NAME AllTests COMMAND DiceRollTests)
enable_testing()