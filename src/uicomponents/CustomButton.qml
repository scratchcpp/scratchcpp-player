// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls

Button {
    id: control
    Material.roundedScale: Material.SmallScale
    leftInset: icon.source + icon.name == "" ? 0 : -2
    rightInset: icon.source + icon.name == "" ? 0 : 5
}
