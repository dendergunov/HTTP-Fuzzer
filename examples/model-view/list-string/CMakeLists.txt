add_executable(list-string
    liststring.cpp
    liststringwidget.hpp
    liststringwidget.cpp
    liststringwidget.ui)

target_compile_features(list-string PRIVATE cxx_std_20)

target_link_libraries(list-string PRIVATE
    Qt5::Widgets)

ntc_target(list-string)
