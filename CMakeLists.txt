cmake_minimum_required(VERSION 3.28)

project(DiceRoll)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest CONFIG REQUIRED)
find_package(ftxui REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(JSONCPP jsoncpp)

add_executable(DiceRoll
    src/main.cpp
)

target_sources(DiceRoll
    PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES
        FILES src/character.cppm
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
    ${JSONCPP_LIBRARIES})

target_link_libraries(DiceRoll PRIVATE 
    ${JSONCPP_LIBRARIES}
    ftxui::screen
    ftxui::dom
    ftxui::component)

target_include_directories(DiceRoll PRIVATE ${JSONCPP_INCLUDE_DIRS})

add_test(NAME AllTests COMMAND DiceRollTests)
enable_testing()