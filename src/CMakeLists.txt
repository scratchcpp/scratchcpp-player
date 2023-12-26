qt_add_executable(appscratchcpp-player
    main.cpp
)

qt_add_qml_module(appscratchcpp-player
    URI ScratchCPP
    VERSION 1.0
    QML_FILES main.qml
)

add_subdirectory(uicomponents)

target_link_libraries(appscratchcpp-player PRIVATE scratchcpp-uicomponents)
