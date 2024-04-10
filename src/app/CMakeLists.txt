set(APP_TARGET scratchcpp-player CACHE INTERNAL "")

qt_add_executable(${APP_TARGET}
    main.cpp
    app.cpp
    app.h
    appmenubar.cpp
    appmenubar.h
    libraryinfo.cpp
    libraryinfo.h
)

qt_add_qml_module(${APP_TARGET}
    URI ScratchCPP
    VERSION 1.0
    QML_FILES
        qml/main.qml
        qml/dialogs/AboutDialog.qml
        qml/dialogs/ProjectSettingsDialog.qml
)

set(QML_IMPORT_PATH "${QML_IMPORT_PATH};${CMAKE_CURRENT_LIST_DIR}"
    CACHE STRING "Qt Creator extra QML import paths"
    FORCE
)

list(APPEND QML_IMPORT_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
list(REMOVE_DUPLICATES QML_IMPORT_PATH)
set(QML_IMPORT_PATH ${QML_IMPORT_PATH} CACHE STRING "" FORCE)

set_target_properties(${APP_TARGET} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(${APP_TARGET}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_compile_definitions(${APP_TARGET} PRIVATE BUILD_VERSION="${CMAKE_PROJECT_VERSION}")
target_link_libraries(${APP_TARGET} PRIVATE ${QT_LIBS})
target_include_directories(${APP_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(${APP_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../global)

target_link_libraries(${APP_TARGET} PRIVATE scratchcpp-render scratchcpp-renderplugin)
