set(MODULE uicomponents)
set(MODULE_URI UiComponents)
set(MODULE_QML_FILES
    CustomButton.qml
    CustomToolButton.qml
    AccentButton.qml
    HoverToolTip.qml
    CustomMenuBar.qml
    CustomMenu.qml
    CustomMenuItem.qml
    CustomMenuSeparator.qml
    CustomDialog.qml
    internal/CustomDialogButtonBox.qml
)
set(MODULE_SRC
    uicomponentsmodule.cpp
    uicomponentsmodule.h
    menubarmodel.cpp
    menubarmodel.h
    menumodel.cpp
    menumodel.h
    menuitemmodel.cpp
    menuitemmodel.h
    filedialog.cpp
    filedialog.h
    dialogview.cpp
    dialogview.h
    internal/quickwindow.cpp
    internal/quickwindow.h
)

include(${PROJECT_SOURCE_DIR}/build/module.cmake)

add_subdirectory(test)
