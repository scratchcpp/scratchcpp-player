// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

ToolTip {
    visible: parent.hovered && text != ""
    delay: 500
}
