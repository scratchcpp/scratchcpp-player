qt_add_resources(
    ${APP_TARGET} "icon_theme"
    PREFIX "/icons/scratchcpp"
    FILES
        index.theme
)

qt_add_resources(
    ${APP_TARGET} "icons"
    PREFIX "/icons/scratchcpp/32x32"
    FILES
        green_flag.svg
        stop.svg
        turbo.svg
)
