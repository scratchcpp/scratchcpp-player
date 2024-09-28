// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import ScratchCPP.Ui

RoundButton {
	property color color: Material.background
	id: control
	onColorChanged: Material.background = color

	Rectangle {
		width: control.background.width
		height: control.background.height
		anchors.centerIn: parent
		radius: width / 2
		color: Qt.rgba(0, 0, 0, 0)
		border.color: ThemeEngine.borderColor
	}

	Rectangle {
		visible: control.checked
		width: control.background.width + 6
		height: control.background.height + 6
		anchors.centerIn: parent
		radius: width / 2
		color: Qt.rgba(0, 0, 0, 0)
		border.color: ThemeEngine.foregroundColor
	}
}
