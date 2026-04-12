cmake_minimum_required(VERSION 3.13)

project(NombreDeTuMod)

find_package(Geode REQUIRED)

add_geode_mod(
        ${PROJECT_NAME}
            SOURCES
                    src/main.cpp
)

)