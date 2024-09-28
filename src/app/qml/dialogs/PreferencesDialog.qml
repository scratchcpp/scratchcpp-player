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
    }
}
