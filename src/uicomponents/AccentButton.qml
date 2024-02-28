// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls.Material

CustomButton {
    readonly property color accent: Material.accent
    Material.foreground: Material.theme == Material.Dark ? "white" : "black"
    Material.background: Qt.rgba(accent.r, accent.g, accent.b, 0.3)
    background.layer.enabled: false
    font.capitalization: Font.MixedCase
}
