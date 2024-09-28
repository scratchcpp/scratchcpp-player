// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import ScratchCPP.Ui
import "internal"

Item {
    id: root

    property Component contentItem: Item {}
    readonly property alias contents: dialog.contents
    property int standardButtons
    property string title: Qt.application.displayName
    property bool fixedSize: true
    property bool maximized: false
    property bool autoClose: true
    property int nativeDialogMinimumWidth: dialog.contentItem.contentLayout.implicitWidth
    property int nativeDialogMinimumHeight: dialog.contentItem.contentLayout.implicitHeight
    readonly property bool isNative: true
    property bool closable: true
    signal accepted()
    signal applied()
    signal discarded()
    signal helpRequested()
    signal rejected()
    signal reset()
    signal opened()
    signal closed()
    signal aboutToShow()
    signal aboutToHide()
    signal focusReset()

    visible: dialog.visible

    onVisibleChanged: {
        if (!priv.initialized) {
            priv.initialized = true;
            return;
        }

        priv.contentsActive = visible;
        dialog.visible = visible;

        if (visible) {
            UiEngine.activeFocusItem = dialog.activeFocusItem;
            aboutToShow();
            opened();
            priv.sizeUpdate = !priv.sizeUpdate;
        } else {
            aboutToHide();
            closed();

            if (!priv.closedFromQml)
                rejected();
        }

        priv.closedFromQml = false;
        visible = Qt.binding(function() { return dialog.visible });
    }

    onMaximizedChanged: {
        if (maximized)
            dialog.setMaximizedState();
        else
            dialog.setNormalState();
    }

    function open() {
        visible = true;
    }

    function close() {
        priv.closedFromQml = true;
        visible = false;
    }

    function accept() {
        close();
        accepted();
    }

    function reject() {
        close();
        rejected();
    }

    function standardButton(button) {
        return dialog.contentItem.buttonBoxLoader.item.standardButton(button);
    }

    QtObject {
        id: priv
        property bool closedFromQml: true
        property bool initialized: false
        property bool sizeUpdate: false
        property bool contentsActive: true
    }

    DialogView {
        readonly property Item contents: contentItem.contentsLoader.item
        id: dialog
        title: root.title
        visible: false
        autoClose: root.autoClose
        closable: root.closable
        minimumWidth: nativeDialogMinimumWidth
        minimumHeight: nativeDialogMinimumHeight
        maximumWidth: {
            priv.sizeUpdate;
            return fixedSize ? Math.max(contentItem.contentLayout.implicitWidth, minimumWidth) : { maximumWidth = maximumWidth };
        }
        maximumHeight: {
            priv.sizeUpdate;
            return fixedSize? Math.max(contentItem.contentLayout.implicitHeight, minimumHeight) : { maximumHeight = maximumHeight };
        }
        onActiveFocusItemChanged: UiEngine.activeFocusItem = activeFocusItem

        contentItem: Rectangle {
            property alias contentLayout: contentLayout
            property alias contentsLoader: contentsLoader
            property alias buttonBoxLoader: buttonBoxLoader
            anchors.fill: parent
            // TODO: Read colors from ThemeEngine
            color: ThemeEngine.bgColor
            Material.background: ThemeEngine.bgColor
            //Material.accent: ThemeEngine.currentAccentColor
            Material.theme: ThemeEngine.theme === ThemeEngine.DarkTheme ? Material.Dark : Material.Light

            ColumnLayout {
                id: contentLayout
                anchors.fill: parent

                Loader {
                    id: contentsLoader
                    sourceComponent: root.contentItem
                    active: priv.contentsActive
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }

                Loader {
                    id: buttonBoxLoader

                    sourceComponent: CustomDialogButtonBox {
                        standardButtons: root.standardButtons
                        onAccepted: root.accept()
                        onApplied: root.applied()
                        onDiscarded: root.discarded()
                        onHelpRequested: root.helpRequested()
                        onRejected: root.reject()
                        onReset: root.reset()
                        onFocusOut: {
                            root.focusReset();
                            root.forceActiveFocus(Qt.TabFocusReason);
                        }
                    }

                    Layout.fillWidth: true

                    /*Connections {
                        target: LanguageManager

                        function onLanguageChanged() {
                            translationTimer.start();
                        }
                    }

                    Timer {
                        id: translationTimer
                        interval: 16
                        running: false
                        repeat: false
                        onTriggered: {
                            buttonBoxLoader.active = 0;
                            buttonBoxLoader.active = 1;
                        }
                    }*/
                }
            }
        }
    }

    Component.onCompleted: {
        if (!visible)
            priv.contentsActive = false;

        maximizedChanged();
    }
}
