cmake_minimum_required(VERSION 3.13)

project(CustomRateLayouts VERSION 1.0.0 LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    Geode
    GIT_REPOSITORY https://github.com/geode-sdk/geode.git
    GIT_TAG main
)

FetchContent_MakeAvailable(Geode)

add_geode_mod(
    teamdev.custom_rate_layouts
    VERSION 1.0.0
    SOURCES 
        src/main.cpp
    RESOURCES
        resources/custom_rate_icon.png
)

target_compile_features(teamdev.custom_rate_layouts PUBLIC cxx_std_20)
