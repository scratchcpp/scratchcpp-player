// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import ScratchCPP
import ScratchCPP.UiComponents
import ScratchCPP.Render
import ScratchCPP.Keyboard

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

        Connections {
            target: AppMenuBar

            function onFileOpened(fileName) {
                urlField.text = fileName;
                player.fileName = fileName;
            }
        }
    }

    ColumnLayout {
        id: layout
        anchors.fill: parent
        anchors.margins: 10

        RowLayout {
            Layout.fillWidth: true

            CustomToolButton {
                id: greenFlagButton
                icon.name: "green_flag"
                icon.color: "transparent"
                onClicked: {
                    if (KeyboardInfo.keyboardModifiers() === Qt.ShiftModifier)
                        AppMenuBar.turboMode = !AppMenuBar.turboMode
                    else {
                        player.stop()
                        player.start()
                        player.forceActiveFocus(Qt.TabFocusReason);
                    }
                }
            }

            CustomToolButton {
                icon.name: "stop"
                icon.color: "transparent"
                onClicked: {
                    player.stop()
                }
            }

            IconLabel {
                icon.name: "turbo"
                icon.color: "transparent"
                text: qsTr("Turbo Mode")
                color: Qt.rgba(1, 0.67, 0.1, 1)
                visible: AppMenuBar.turboMode

                font {
                    // Reuse the font from the green flag button
                    family: greenFlagButton.font.family
                    capitalization: Font.MixedCase
                    pointSize: 8
                    bold: true
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
            turboMode: AppMenuBar.turboMode
            stageRect.border.color: Material.theme == Material.Dark ? Qt.rgba(1, 1, 1, 0.15) : Qt.rgba(0, 0, 0, 0.15)
            stageRect.border.width: 5
        }
    }
}
