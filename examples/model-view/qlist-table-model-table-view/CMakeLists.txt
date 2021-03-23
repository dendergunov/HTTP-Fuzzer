add_executable(qlist-table-mv
    qlisttable.cpp
    qlisttablewidget.cpp
    qlisttablewidget.hpp
    qlisttablewidget.ui
    pairstringmodel.cpp
    pairstringmodel.hpp)

target_compile_features(qlist-table-mv PRIVATE cxx_std_20)

target_link_libraries(qlist-table-mv PRIVATE
    Qt5::Widgets)

ntc_target(qlist-table-mv)
