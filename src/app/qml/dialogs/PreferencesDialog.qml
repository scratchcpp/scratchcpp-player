// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScratchCPP.Global
import ScratchCPP.Ui
import ScratchCPP.UiComponents

import ".."

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
                model: ThemeEngine.theme == ThemeEngine.DarkTheme ? Colors.darkAccentColors : Colors.lightAccentColors

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
                if(ThemeEngine.theme == ThemeEngine.DarkTheme) {
                    ThemeEngine.accentColor = Colors.darkAccentColors[priv.accentColorIndex];
                } else {
                    ThemeEngine.accentColor = Colors.lightAccentColors[priv.accentColorIndex];
                }
            }
        }
    }
}
