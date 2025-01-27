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
    color: ThemeEngine.bgColor
    Material.accent: ThemeEngine.accentColor
    Material.theme: ThemeEngine.theme == ThemeEngine.DarkTheme ? Material.Dark : Material.Light
    onActiveFocusItemChanged: UiEngine.activeFocusItem = activeFocusItem

    menuBar: CustomMenuBar {
        width: root.width
        model: AppMenuBar.model

        Connections {
            target: AppMenuBar

            function onFileOpened(fileName) {
                urlField.text = fileName;
                player.load(fileName);
            }

            function onFps60ModeChanged() {
                if(AppMenuBar.fps60Mode)
                    player.fps = 60;
                else if(player.fps === 60)
                    player.fps = 30;
            }

            function onProjectSettingsTriggered() {
                projectSettingsDialog.open();
            }

            function onPreferencesTriggered() {
                preferencesDialog.open();
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

    PreferencesDialog { id: preferencesDialog }

    CustomMessageDialog {
        id: unsupportedBlocksDialog
        title: qsTr("Warning")
        text: qsTr("This project contains unsupported blocks:")
        informativeText: player.unsupportedBlocks.join('\r\n')
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
                highlighted: player.running
                onClicked: {
                    switch (KeyboardInfo.keyboardModifiers()) {
                        case Qt.ShiftModifier:
                            AppMenuBar.turboMode = !AppMenuBar.turboMode
                            break;

                        case Qt.AltModifier:
                            AppMenuBar.fps60Mode = !AppMenuBar.fps60Mode
                            break;

                        case Qt.ControlModifier:
                            AppMenuBar.mute = !AppMenuBar.mute
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
                icon.name: "mute"
                icon.color: "transparent"
                text: ""
                visible: AppMenuBar.mute
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
                onClicked: player.load(urlField.text)
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
            mute: AppMenuBar.mute
            onLoaded: {
                if(unsupportedBlocks.length > 0)
                    unsupportedBlocksDialog.open()

                currentFps.enable = true;
            }

            Loader {
                id: currentFps
                property bool enable: false
                active: projectSettingsDialog.showCurrentFps && enable
                anchors.right: player.stageRect.right
                anchors.top: player.stageRect.top

                sourceComponent: Text {
                    text: player.renderFps
                    font.pointSize: 20 * player.stageScale
                    font.family: "mono"
                    color: Qt.rgba(1, 0, 0, 0.75)
                    style: Text.Outline
                    styleColor: "black"
                }
            }
        }
    }

    Component.onCompleted: {
        if(ThemeEngine.accentColor === Qt.rgba(0, 0, 0, 0))
            ThemeEngine.accentColor = Colors.defaultAccentColor;
    }
}
