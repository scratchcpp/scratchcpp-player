// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import ScratchCPP
import ScratchCPP.UiComponents
import ScratchCPP.Render

ApplicationWindow {
    id: root
    minimumWidth: layout.implicitWidth + layout.anchors.margins * 2
    minimumHeight: menuBar.height + layout.implicitHeight + layout.anchors.margins * 2
	visible: true
    title: "ScratchCPP"
    color: Material.background
    Material.accent: "orange"
    Material.theme: Material.Dark

    menuBar: CustomMenuBar {
        width: root.width
        model: AppMenuBar.model
    }

    ColumnLayout {
        id: layout
        anchors.fill: parent
        anchors.margins: 10

        RowLayout {
            Layout.fillWidth: true

            CustomToolButton {
                icon.name: "green_flag"
                icon.color: "transparent"
                onClicked: {
                    player.stop()
                    player.start()
                    player.forceActiveFocus(Qt.TabFocusReason);
                }
            }

            CustomToolButton {
                icon.name: "stop"
                icon.color: "transparent"
                onClicked: {
                    player.stop()
                }
            }

            TextField {
                id: urlField
                Layout.fillWidth: true
                placeholderText: qsTr("Project URL")
            }

            CustomToolButton {
                text: qsTr("Load")
                onClicked: player.fileName = urlField.text
            }
        }

        ProjectPlayer {
            id: player
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: stageWidth
            Layout.minimumHeight: stageHeight
            activeFocusOnTab: true
            focus: true
            spriteFencing: false
            stageRect.border.color: Material.theme == Material.Dark ? Qt.rgba(1, 1, 1, 0.15) : Qt.rgba(0, 0, 0, 0.15)
            stageRect.border.width: 5
        }
    }
}
