// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import ScratchCPP
import ScratchCPP.Ui
import ScratchCPP.UiComponents
import ScratchCPP.Render
import ScratchCPP.Keyboard
import "dialogs"

ApplicationWindow {
    id: root
    minimumWidth: layout.implicitWidth + layout.anchors.margins * 2
    minimumHeight: menuBar.height + layout.implicitHeight + layout.anchors.margins * 2
	visible: true
    title: Qt.application.displayName
    color: Material.background
    Material.accent: "orange"
    Material.theme: Material.Dark
    onActiveFocusItemChanged: UiEngine.activeFocusItem = activeFocusItem

    menuBar: CustomMenuBar {
        width: root.width
        model: AppMenuBar.model

        Connections {
            target: AppMenuBar

            function onFileOpened(fileName) {
                urlField.text = fileName;
                player.fileName = fileName;
            }

            function onProjectSettingsTriggered() {
                projectSettingsDialog.open();
            }

            function onAboutAppTriggered() {
                aboutDialog.open();
            }
        }
    }

    AboutDialog { id: aboutDialog }

    ProjectSettingsDialog {
        id: projectSettingsDialog
        projectPlayer: player
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
                    switch (KeyboardInfo.keyboardModifiers()) {
                        case Qt.ShiftModifier:
                            AppMenuBar.turboMode = !AppMenuBar.turboMode
                            break;

                        case Qt.AltModifier:
                            AppMenuBar.fps60Mode = !AppMenuBar.fps60Mode
                            break;

                        default:
                            player.stop()
                            player.start()
                            player.forceActiveFocus(Qt.TabFocusReason);
                            break;
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

            Label {
                text: qsTr("%1 FPS").arg(player.fps)
                color: Qt.rgba(1, 0.67, 0.1, 1)
                visible: player.fps !== 30
                font.pointSize: 8
                font.bold: true
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
            turboMode: AppMenuBar.turboMode
            fps: AppMenuBar.fps60Mode ? 60 : 30
        }
    }
}
