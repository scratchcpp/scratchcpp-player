set(APP_TARGET scratchcpp-player CACHE INTERNAL "")

qt_add_executable(${APP_TARGET}
    main.cpp
)

qt_add_qml_module(${APP_TARGET}
    URI ScratchCPP
    VERSION 1.0
    QML_FILES main.qml
)

set_target_properties(${APP_TARGET} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(${APP_TARGET}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${APP_TARGET}
    PRIVATE Qt6::Quick Qt6::QuickControls2)

target_link_libraries(${APP_TARGET} PRIVATE scratchcpp-render scratchcpp-renderplugin)
