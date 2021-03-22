add_executable(httpspost
    post.cpp
    httpsmanager.cpp
    httpsmanager.hpp)

target_compile_features(httpspost PRIVATE cxx_std_20)

target_link_libraries(httpspost PRIVATE
    Qt5::Network)

ntc_target(httpspost)
