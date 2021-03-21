add_executable(httpget 
    httpget.cpp
    httpmanager.cpp
    httpmanager.hpp)

target_compile_features(httpget PRIVATE cxx_std_20)

target_link_libraries(httpget PRIVATE
    Qt5::Network)

ntc_target(httpget)
