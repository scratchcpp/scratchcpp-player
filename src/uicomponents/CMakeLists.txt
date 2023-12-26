qt_add_library(scratchcpp-uicomponents STATIC)

set_target_properties(scratchcpp-uicomponents PROPERTIES AUTOMOC ON)

qt_add_qml_module(scratchcpp-uicomponents
    URI ScratchCPP.UiComponents
    VERSION 1.0
    NO_PLUGIN
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ScratchCPP/UiComponents
    QML_FILES
        CustomButton.qml
	CustomToolButton.qml
	HoverToolTip.qml
)

set(QML_IMPORT_PATH "${QML_IMPORT_PATH};${CMAKE_CURRENT_LIST_DIR}"
    CACHE STRING "Qt Creator extra QML import paths"
    FORCE
)

list(APPEND QML_IMPORT_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
list(REMOVE_DUPLICATES QML_IMPORT_PATH)
set(QML_IMPORT_PATH ${QML_IMPORT_PATH} CACHE STRING "" FORCE)
