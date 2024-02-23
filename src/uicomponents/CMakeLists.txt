set(MODULE uicomponents)
set(MODULE_URI UiComponents)
set(MODULE_QML_FILES
    CustomButton.qml
    CustomToolButton.qml
    HoverToolTip.qml
)
set(MODULE_SRC
    menubarmodel.cpp
    menubarmodel.h
    menumodel.cpp
    menumodel.h
    menuitemmodel.cpp
    menuitemmodel.h
)

include(${PROJECT_SOURCE_DIR}/build/module.cmake)

add_subdirectory(test)
