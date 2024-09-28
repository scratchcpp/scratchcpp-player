// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import ScratchCPP.Ui

DialogButtonBox {
    property int radius: 10
    signal focusOut()
    id: dialogButtonBox
    font.capitalization: Font.MixedCase
    background: Rectangle {
        color: "transparent"
        radius: radius
    }

    QtObject {
        id: priv
        readonly property var standardButtons: [
            Dialog.Ok, Dialog.Open, Dialog.Save,
            Dialog.Cancel, Dialog.Close, Dialog.Discard,
            Dialog.Apply, Dialog.Reset, Dialog.RestoreDefaults,
            Dialog.Help, Dialog.SaveAll, Dialog.Yes,
            Dialog.YesToAll, Dialog.No, Dialog.NoToAll,
            Dialog.Abort, Dialog.Retry, Dialog.Ignore
        ]
    }

    function retranslateButtons() {
        for (let i = 0; i < priv.standardButtons.length; i++) {
            let standardBtn = priv.standardButtons[i];
            let button = standardButton(standardBtn);

            if (button)
                button.text = UiEngine.standardButtonText(standardBtn);
        }
    }

    Connections {
        readonly property Item firstButton: dialogButtonBox.contentChildren[0]
        target: firstButton

        function onActiveFocusChanged() {
            if (!firstButton.activeFocus)
                focusOut();
        }
    }

    Component.onCompleted: retranslateButtons()
    onStandardButtonsChanged: retranslateButtons()
}
