// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScratchCPP.Global
import ScratchCPP.Ui
import ScratchCPP.UiComponents

CustomDialog {
    title: qsTr("Preferences")
    standardButtons: Dialog.Cancel | Dialog.Ok
    onOpened: Settings.freeze()
    onAccepted: Settings.saveChanges()
    onRejected: {
        Settings.discardChanges();
        ThemeEngine.reloadTheme();
    }

    QtObject {
        id: priv
        property int accentColorIndex: -1

        readonly property list<color> darkAccentColors: [
            Qt.rgba(0.85, 0.31, 0.33, 1),
            Qt.rgba(0.85, 0.62, 0.31, 1),
            Qt.rgba(0.85, 0.84, 0.31, 1),
            Qt.rgba(0.39, 0.85, 0.31, 1),
            Qt.rgba(0.31, 0.75, 0.85, 1),
            Qt.rgba(0.32, 0.32, 0.85, 1),
            Qt.rgba(0.68, 0.31, 0.85, 1),
        ]

        readonly property list<color> lightAccentColors: [
            Qt.rgba(0.75, 0.08, 0.09, 1),
            Qt.rgba(0.75, 0.47, 0.08, 1),
            Qt.rgba(0.75, 0.74, 0.08, 1),
            Qt.rgba(0.17, 0.75, 0.08, 1),
            Qt.rgba(0.08, 0.63, 0.75, 1),
            Qt.rgba(0.08, 0.08, 0.75, 1),
            Qt.rgba(0.54, 0.08, 0.75, 1),
        ]
    }

    contentItem: ColumnLayout {
        // Themes
        Label {
            text: qsTr("Themes")
            font.pointSize: 14
            font.bold: true
        }

        RowLayout {
            RadioButton {
                text: qsTr("Light")
                checked: ThemeEngine.theme === ThemeEngine.LightTheme
                onCheckedChanged: if(checked) ThemeEngine.theme = ThemeEngine.LightTheme
            }

            RadioButton {
                text: qsTr("Dark")
                checked: ThemeEngine.theme === ThemeEngine.DarkTheme
                onCheckedChanged: if(checked) ThemeEngine.theme = ThemeEngine.DarkTheme
            }
        }

        RowLayout {
            Label {
                text: qsTr("Accent color:")
            }

            Repeater {
                id: accentColors
                model: ThemeEngine.theme == ThemeEngine.DarkTheme ? priv.darkAccentColors : priv.lightAccentColors

                ColorButton {
                    required property color modelData
                    required property int index
                    color: modelData
                    checked: {
                        if(ThemeEngine.accentColor === modelData) {
                            priv.accentColorIndex = index;
                            return true;
                        } else {
                            return false;
                        }
                    }
                    autoExclusive: true
                    checkable: true
                    onPressed: ThemeEngine.accentColor = modelData;
                }
            }
        }

        Connections {
            target: ThemeEngine

            function onThemeChanged() {
                console.log(priv.accentColorIndex, ThemeEngine.theme);

                if(ThemeEngine.theme == ThemeEngine.DarkTheme) {
                    ThemeEngine.accentColor = priv.darkAccentColors[priv.accentColorIndex];
                } else {
                    ThemeEngine.accentColor = priv.lightAccentColors[priv.accentColorIndex];
                }
            }
        }
    }
}
