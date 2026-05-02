cmake_minimum_required(VERSION 3.10)

project(CompilersAndAutomata)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES
    src/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        src
        src/utils
        src/automata/dfa
)

# Test Executable
file(GLOB_RECURSE TEST_FILES
    tests/*.cpp
)

# Remove src/main.cpp from test build
list(REMOVE_ITEM SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_executable(tests_runner
    ${TEST_FILES}
    ${SRC_FILES}
)

target_include_directories(tests_runner
    PRIVATE
        src
        src/utils
        tests
)
