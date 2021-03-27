cmake_minimum_required(VERSION 3.16)

project(HTTP-Fuzzer
    DESCRIPTION "HTTP Fuzzer build on Qt framework"
    VERSION 0.0.0
    LANGUAGES CXX)

find_package(ntc-cmake 1.1.0 REQUIRED)
include(ntc-dev-build)

find_package(Qt5 5.15.2 COMPONENTS Widgets LinguistTools Network REQUIRED)

add_executable(HTTP-Fuzzer
    src/main.cpp
    src/repeater/guirepeater.cpp
    src/repeater/guirepeater.hpp
    src/repeater/guirepeater.ui
    src/repeater/replyheadermodel.cpp
    src/repeater/replyheadermodel.hpp
    src/repeater/requestheadermodel.cpp
    src/repeater/requestheadermodel.hpp
    src/fuzzer/fuzzwidget.cpp
    src/fuzzer/fuzzwidget.hpp
    src/fuzzer/fuzzwidget.ui
    src/fuzzer/payloadmodel.cpp
    src/fuzzer/payloadmodel.hpp
    src/fuzzer/payloadlistdelegate.cpp
    src/fuzzer/payloadlistdelegate.hpp
    src/fuzzer/substringindexdelegate.cpp
    src/fuzzer/substringindexdelegate.hpp
    src/fuzzer/substringindexesinputdialog.cpp
    src/fuzzer/substringindexesinputdialog.hpp
    src/fuzzer/substringindexesinputdialog.ui
    src/fuzzer/customtypes.hpp
    src/fuzzer/fuzzmanager.cpp
    src/fuzzer/fuzzmanager.hpp
    src/fuzzer/requestresultmodel.cpp
    src/fuzzer/requestresultmodel.hpp
  )

target_compile_features(HTTP-Fuzzer PRIVATE cxx_std_20)

target_link_libraries(HTTP-Fuzzer PRIVATE
    Qt5::Widgets
    Qt5::Network)

ntc_target(HTTP-Fuzzer)

option(FUZZ_BUILD_EXAMPLES "Build examples of components used in the project" OFF)

if(FUZZ_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
