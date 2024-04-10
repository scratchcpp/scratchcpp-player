// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScratchCPP.UiComponents
import ScratchCPP.Render

CustomDialog {
    property ProjectPlayer projectPlayer: null
    title: qsTr("Project settings")
    standardButtons: Dialog.Close

    contentItem: RowLayout {}
}
