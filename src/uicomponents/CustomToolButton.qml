// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import ScratchCPP.Ui

// Similar to ToolButton, but it's always a (rounded) rectangle
// Double click events are not supported, use the clicked() signal like with a QPushButton
CustomButton {
    property color foregroundColor: ThemeEngine.foregroundColor
    property string toolTipText
    property string accessibleDescription: ""
    signal clicked()
    id: control
    font.capitalization: Font.MixedCase
    Material.background: Qt.rgba(foregroundColor.r, foregroundColor.g, foregroundColor.b, 0.15)
    Material.foreground: foregroundColor
    icon.color: foregroundColor
    onReleased: clicked()
    HoverToolTip { text: toolTipText }
    Accessible.role: Accessible.Button
    Accessible.name: text
    Accessible.description: accessibleDescription == "" ? toolTipText : accessibleDescription
}
