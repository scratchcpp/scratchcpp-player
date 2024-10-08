// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import ScratchCPP.Ui

Menu {
    property bool isSubMenu: false

    function updateWidth() {
        let maxWidth = 0;

        for (let i = 0; i < count; i++)
            maxWidth = Math.max(maxWidth, itemAt(i).implicitWidth);

        background.implicitWidth = maxWidth;
    }

    function toggle() {
        if (visible)
            close();
        else
            open();
    }

    x: isSubMenu ? parent.width : 0
    y: isSubMenu ? 0 : parent.height
    font.pointSize: 10
    background: Rectangle {
        // Load colors from theme
        color: ThemeEngine.bgColor
        border.color: ThemeEngine.borderColor
        radius: 10
        implicitHeight: 40
    }
    delegate: CustomMenuItem {}
    onAboutToShow: updateWidth()
}
