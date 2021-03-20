cmake_minimum_required(VERSION 3.16)

project(HTTP-Fuzzer
    DESCRIPTION "Simple HTTP Fuzzer to practice Qt framework"
    VERSION 0.0.0
    LANGUAGES CXX)

find_package(ntc-cmake 1.1.0 REQUIRED)
include(ntc-dev-build)

find_package(Qt5 5.13.2 COMPONENTS Widgets LinguistTools REQUIRED)

add_executable(HTTP-Fuzzer
    src/main.cpp
    src/fuzzwidget.cpp
    src/fuzzwidget.hpp
    src/fuzzwidget.ui
  )

target_compile_features(HTTP-Fuzzer PRIVATE cxx_std_20)

target_link_libraries(HTTP-Fuzzer PRIVATE Qt5::Widgets)

ntc_target(HTTP-Fuzzer TRANSLATIONS ru)
