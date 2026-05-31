cmake_minimum_required(VERSION 3.16)
project(ElectricalPowerMonitor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(PowerMonitor
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries(PowerMonitor PRIVATE Qt6::Widgets)
