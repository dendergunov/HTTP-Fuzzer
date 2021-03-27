add_executable(fuzz-manager
    fuzzmanager.cpp
    fuzzmanager.hpp
    fuzzwidget.cpp
    fuzzwidget.hpp
    fuzzwidget.ui
    requestresult.hpp
    main.cpp
    requestresultmodel.cpp
    requestresultmodel.hpp)

target_compile_features(fuzz-manager PRIVATE cxx_std_20)

target_link_libraries(fuzz-manager PRIVATE
    Qt5::Network
    Qt5::Widgets)

ntc_target(fuzz-manager)
