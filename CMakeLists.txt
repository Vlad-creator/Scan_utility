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

# parallel main
set(CMAKE_CXX_FLAGS  "-pthread -lpthread")
add_executable(${PROJECT_NAME}_PAR ${HEADERS} ${SRCs})
target_compile_definitions(${PROJECT_NAME}_PAR PRIVATE PARALLEL)

# test
set(TEST_DIR_PATH_1 ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_DIR}/e2e_tests_check_file)
set(TEST_DIR_PATH_2 ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_DIR}/e2e_tests_main)
set(TEST_DIR_PATH_ANSW ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_DIR}/e2e_tests_main_result)

configure_file(${TEST}.in ${TEST} @ONLY)

add_executable(RunUnitTests ${SRCs} ${HEADERS} ${CMAKE_BINARY_DIR}/${TEST_DIR})
target_compile_definitions(RunUnitTests PRIVATE TEST)

# test parallel
add_executable(RunUnitTests_par ${SRCs} ${HEADERS} ${CMAKE_BINARY_DIR}/${TEST_DIR})
target_compile_definitions(RunUnitTests_par PRIVATE TEST PARALLEL)

include(GoogleTest)
gtest_discover_tests(RunUnitTests)

target_include_directories(RunUnitTests PRIVATE ${TEST_DIR})
target_include_directories(RunUnitTests PRIVATE include)
target_include_directories(RunUnitTests PRIVATE src)

target_link_libraries(RunUnitTests gtest gtest_main)


gtest_discover_tests(RunUnitTests_par)

target_include_directories(RunUnitTests_par PRIVATE ${TEST_DIR})
target_include_directories(RunUnitTests_par PRIVATE include)
target_include_directories(RunUnitTests_par PRIVATE src)

target_link_libraries(RunUnitTests_par gtest gtest_main)

