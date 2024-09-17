// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

CustomDialog {
    id: root
    property string text
    property string informativeText
    standardButtons: Dialog.Ok

    contentItem: RowLayout {
        spacing: 25

        // TODO: Add icon

        ColumnLayout {
            Label {
                text: root.text
                font.pointSize: 14
                font.bold: true
            }

            Label {
                text: root.informativeText
            }
        }
    }
}
