// SPDX-License-Identifier: GPL-3.0-or-later

pragma Singleton
import QtQuick
import ScratchCPP.Ui

QtObject {
    readonly property list<color> darkAccentColors: [
        Qt.rgba(0.85, 0.31, 0.33, 1),
        Qt.rgba(0.85, 0.62, 0.31, 1),
        Qt.rgba(0.85, 0.84, 0.31, 1),
        Qt.rgba(0.39, 0.85, 0.31, 1),
        Qt.rgba(0.31, 0.75, 0.85, 1),
        Qt.rgba(0.32, 0.32, 0.85, 1),
        Qt.rgba(0.68, 0.31, 0.85, 1),
    ]

    readonly property list<color> lightAccentColors: [
        Qt.rgba(0.75, 0.08, 0.09, 1),
        Qt.rgba(0.75, 0.47, 0.08, 1),
        Qt.rgba(0.75, 0.74, 0.08, 1),
        Qt.rgba(0.17, 0.75, 0.08, 1),
        Qt.rgba(0.08, 0.63, 0.75, 1),
        Qt.rgba(0.08, 0.08, 0.75, 1),
        Qt.rgba(0.54, 0.08, 0.75, 1),
    ]

    readonly property color defaultAccentColor: ThemeEngine.theme == ThemeEngine.DarkTheme ? darkAccentColors[1] : lightAccentColors[1]
}
