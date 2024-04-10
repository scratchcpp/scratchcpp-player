// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScratchCPP.UiComponents
import ScratchCPP.Render

CustomDialog {
    property ProjectPlayer projectPlayer: null
    title: qsTr("Project settings")
    standardButtons: Dialog.Close

    contentItem: ColumnLayout {
        Label {
            text: qsTr("Remove limits")
            font.pointSize: 14
            font.bold: true
        }

        CheckBox {
            text: qsTr("Infinite clones")
            checked: projectPlayer.cloneLimit === -1
            onCheckedChanged: projectPlayer.cloneLimit = checked ? -1 : 300
        }

        CheckBox {
            text: qsTr("Remove sprite fencing")
            checked: !projectPlayer.spriteFencing
            onCheckedChanged: projectPlayer.spriteFencing = !checked
        }
    }
}
