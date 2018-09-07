cmake_minimum_required(VERSION 3.8.2)
project(CellularAutomaton)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 REQUIRED graphics window system)

set(SOURCES 
    Source/BriansBrain/BriansBrain.cpp
    Source/GameOfLife/GameOfLife.cpp 
    Source/LangtonsAnt/Ant.cpp 
    Source/LangtonsAnt/LangtonsAnt.cpp
    Source/Native/Win32.cpp
    Source/Native/Unix.cpp
    Source/PredatorAndPrey/Creature.cpp 
    Source/PredatorAndPrey/PredatorAndPrey.cpp 
    Source/ResourceManager/ResourceHolder.cpp
    Source/Util/FPSCounter.cpp 
    Source/Util/Random.cpp 
    Source/WireWorld/LineInputMode.cpp
    Source/WireWorld/PointInputMode.cpp 
    Source/WireWorld/WireWorld.cpp
    Source/Application.cpp 
    Source/CellularAutomaton.cpp 
    Source/Main.cpp
)

add_executable(cellular_automaton ${SOURCES})

set_property(TARGET cellular_automaton PROPERTY CXX_STANDARD 17)

target_link_libraries(cellular_automaton ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
