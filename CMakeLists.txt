cmake_minimum_required(VERSION 3.14)

project(SCANNER)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDES include)

# Setup testing
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e
)

enable_testing()

FetchContent_MakeAvailable(googletest)

set(TEST_DIR test_scan)

set(HEADERS include/suspicious.hpp include/scan.hpp include/time.hpp include/includes.hpp)
set(SRCs src/scan.cpp src/suspicious.cpp main.cpp)
set(TEST ${TEST_DIR}/start_test.h)

# main
include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})
add_executable(${PROJECT_NAME} ${HEADERS} ${SRCs})

# test
set(TEST_DIR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_DIR}/e2e_tests_check_file)
configure_file(${TEST}.in ${TEST} @ONLY)

add_executable(RunUnitTests ${SRCs} ${HEADERS} ${CMAKE_BINARY_DIR}/${TEST_DIR})
target_compile_definitions(RunUnitTests PRIVATE TEST)

include(GoogleTest)
gtest_discover_tests(RunUnitTests)

target_include_directories(RunUnitTests PRIVATE ${TEST_DIR})
target_include_directories(RunUnitTests PRIVATE include)
target_include_directories(RunUnitTests PRIVATE src)

target_link_libraries(RunUnitTests gtest gtest_main)

