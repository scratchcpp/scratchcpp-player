// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScratchCPP
import ScratchCPP.UiComponents
import ScratchCPP.Render

CustomDialog {
    property ProjectPlayer projectPlayer: null
    property bool showCurrentFps: false
    title: qsTr("Project settings")
    standardButtons: Dialog.Close

    contentItem: ColumnLayout {
        // General
        Label {
            text: qsTr("General")
            font.pointSize: 14
            font.bold: true
        }

        RowLayout {
            Label {
                text: qsTr("FPS (frames per second)")
            }

            SpinBox {
                editable: true
                from: 1
                to: 250
                stepSize: 10
                value: projectPlayer.fps
                onValueChanged: {
                    projectPlayer.fps = value;
                    AppMenuBar.fps60Mode = (value === 60);
                }
            }
        }

        CheckBox {
            text: qsTr("High Quality Pen")
            checked: projectPlayer.hqPen
            onCheckedChanged: projectPlayer.hqPen = checked
        }

        CheckBox {
            id: showFpsCheckBox
            text: qsTr("Show current FPS")
            checked: showCurrentFps
            onCheckedChanged: showCurrentFps = checked
        }

        // Remove limits
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

        // Experimental
        Label {
            text: qsTr("Experimental")
            font.pointSize: 14
            font.bold: true
        }

        RowLayout {
            Label {
                text: qsTr("Custom stage size")
            }

            SpinBox {
                editable: true
                from: 20
                to: 1920
                stepSize: 20
                value: projectPlayer.stageWidth
                onValueChanged: projectPlayer.stageWidth = value
            }

            Label {
                text: "×"
                font.pointSize: 16
            }

            SpinBox {
                editable: true
                from: 20
                to: 1080
                stepSize: 20
                value: projectPlayer.stageHeight
                onValueChanged: projectPlayer.stageHeight = value
            }
        }
    }
}
