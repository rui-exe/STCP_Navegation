cmake_minimum_required(VERSION 3.21)
project(STCP_Navegation)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Files")

add_executable(STCP_Navegation main.cpp graph.cpp graph.h minHeap.h STCP_Operations.cpp STCP_Operations.h Menu.cpp Menu.h)
