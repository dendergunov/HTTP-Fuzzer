add_executable(gui-repeater
    main.cpp
    guirepeater.cpp
    guirepeater.hpp
    guirepeater.ui
    replyheadermodel.cpp
    replyheadermodel.hpp
    requestheadermodel.cpp
    requestheadermodel.hpp
    )

target_compile_features(gui-repeater PRIVATE cxx_std_20)

target_link_libraries(gui-repeater PRIVATE
    Qt5::Widgets
    Qt5::Network
)

ntc_target(gui-repeater)
