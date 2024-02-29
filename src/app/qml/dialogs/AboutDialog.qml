// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScratchCPP.Ui
import ScratchCPP.UiComponents

CustomDialog {
    //: For example "About ScratchCPP" (%1 is the app name)
    title: qsTr("About %1").arg(Qt.application.displayName)
    standardButtons: Dialog.Ok

    contentItem: RowLayout {
        spacing: 25

        /*Image {
            source: "qrc:/res/images/icon.ico"
            sourceSize.width: 60
            sourceSize.height: 60
            Layout.alignment: Qt.AlignTop
        }*/

        ColumnLayout {
            Label {
                text: Qt.application.displayName
                font.bold: true
            }

            Label {}

            Label {
                text: qsTr("Version: %1").arg(Qt.application.version)
            }

            Label {
                text: qsTr("Revision: %1").arg(AppInfo.revision())
            }

            Label {
                readonly property string src: "https://github.com/scratchcpp/scratchcpp-player"
                text: qsTr("Source code: %1").arg("<a href=\"" + src + "\">" + src + "</a>")
                onLinkActivated: (link)=> Qt.openUrlExternally(link)
            }

            Label {}

            Label {
                readonly property int startYear: 2024
                readonly property string startStr: AppInfo.buildYear() === startYear ? "" : startYear + "-"
                text: "Copyright © " + startStr + AppInfo.buildYear() + " adazem009"
            }

            Label {
                text: qsTr("Published with the GNU General Public License.")
            }
        }
    }
}
