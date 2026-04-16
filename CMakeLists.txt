cmake_minimum_required(VERSION 3.25)

project(MiModLayouts)

find_package(Geode CONFIG REQUIRED)

add_geode_mod(
    ${PROJECT_NAME}
    SOURCES src/main.cpp
)
