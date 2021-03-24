add_executable(list-dialog-fill
    listdialogfill.cpp
    payloadwidget.cpp
    payloadwidget.hpp
    payloadwidget.ui
    editpayloaddialog.cpp
    editpayloaddialog.hpp
    editpayloaddialog.ui)

target_compile_features(list-dialog-fill PRIVATE cxx_std_20)

target_link_libraries(list-dialog-fill PRIVATE
    Qt5::Widgets)

ntc_target(list-dialog-fill)
