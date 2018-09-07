cmake_minimum_required(VERSION 3.8.2)
project(CellularAutomaton)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 REQUIRED graphics window system)

file(GLOB_RECURSE SOURCE ./Source/*.cpp)

add_executable(cellular_automaton ${SOURCE})

set_property(TARGET cellular_automaton PROPERTY CXX_STANDARD 17)

target_link_libraries(cellular_automaton ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
