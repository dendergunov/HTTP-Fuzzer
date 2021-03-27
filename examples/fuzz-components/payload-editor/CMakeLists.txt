add_executable(payload-editor
    payloadeditorwidget.cpp
    payloadeditorwidget.hpp
    payloadeditorwidget.ui
    payloadeditor.cpp
    payloadmodel.cpp
    payloadmodel.hpp
    payloadlistdelegate.cpp
    payloadlistdelegate.hpp
    substringindexdelegate.cpp
    substringindexdelegate.hpp
    substringindexesinputdialog.cpp
    substringindexesinputdialog.hpp
    substringindexesinputdialog.ui
    customtypes.hpp
    fuzzmanager.cpp
    fuzzmanager.hpp)


target_compile_features(payload-editor PRIVATE cxx_std_20)

target_link_libraries(payload-editor PRIVATE
    Qt5::Widgets)

ntc_target(payload-editor)
