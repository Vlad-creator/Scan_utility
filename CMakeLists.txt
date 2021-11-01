cmake_minimum_required(VERSION 3.14)

project(SCANNER)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDES include)

set(HEADERS include/suspicious.hpp include/scan.hpp include/time.hpp include/includes.hpp)
set(SRCs src/scan.cpp src/suspicious.cpp main.cpp)

include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})
add_executable(${PROJECT_NAME} ${HEADERS} ${SRCs})

