// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import ScratchCPP.UiComponents

MenuBar {
    id: root
    property MenuBarModel model: MenuBarModel {}

    QtObject {
        id: priv
        readonly property alias menus: root.model.menus
        readonly property var menuObjects: []
    }

    Connections {
        target: root.model

        function onMenusChanged() { reload() }
    }

    function getComponentString(typeName) {
        //var imports = "import QtQuick; import QtQuick.Controls; import Qt.labs.platform as Platform;"
        var imports = "import QtQuick; import QtQuick.Controls;"
        return imports + " " + typeName + " {}";
    }

    function createMenuBar(parentItem, menuType, menuItemType, menuSeparatorType) {
        for(var i = 0; i < priv.menus.length; i++) {
            var menuParent = parentItem;
            var menu = Qt.createQmlObject(getComponentString(menuType), menuParent);
            menu.title = priv.menus[i].title;
            priv.menuObjects[priv.menuObjects.length] = menu;
            parentItem.addMenu(menu);
            createMenu(menu, priv.menus[i].items, menuType, menuItemType, menuSeparatorType);
        }
    }

    function createMenu(parentItem, itemList, menuType, menuItemType, menuSeparatorType) {
        for (let i = 0; i < itemList.length; i++) {
            let itemData = itemList[i];
            let itemComponent;
            let item;
            let overrideAddItem = false;

            if (itemData.isSeparator) {
                item = Qt.createQmlObject(getComponentString(menuSeparatorType), parentItem);
            } else if (itemData.submenu === null) {
                item = Qt.createQmlObject(getComponentString(menuItemType), parentItem);
                item.text = itemData.text;
                item.checkable = itemData.checkable;
                item.checked = itemData.checked;
                item.enabled = itemData.enabled;
                item.onCheckedChanged.connect(function() { itemData.checked = item.checked; });
                itemData.onCheckedChanged.connect(function() { item.checked = itemData.checked; });
                itemData.onEnabledChanged.connect(function() { item.enabled = itemData.enabled; });

                if (typeof itemData.onClicked != "undefined")
                    item.onTriggered.connect(function() { itemData.onClicked() });
            } else {
                item = Qt.createQmlObject(getComponentString(menuType), parentItem)
                item.title = itemData.text;
                parentItem.addMenu(item);
                createMenu(item, itemData.submenu.items, menuType, menuItemType, menuSeparatorType);
                overrideAddItem = true;
            }

            if (!overrideAddItem)
                parentItem.addItem(item);
        }
    }

    background: Rectangle {
        color: Material.backgroundColor // Load the color from the theme
    }

    delegate: MenuBarItem {
        id: menuBarItem

        function replaceText(txt)
        {
            var index = txt.indexOf("&");

            if (index >= 0)
                txt = txt.replace(txt.substr(index, 2), ("<u>" + txt.substr(index + 1, 1) +"</u>"));

            return txt;
        }

        implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding
        leftPadding: 10
        rightPadding: 10
        topPadding: 5
        bottomPadding: 5
        font.pointSize: 10
        Material.background: Qt.rgba(0, 0, 0, 0)
        Material.foreground: Material.theme == Material.Dark ? "white" : "black"
        contentItem: Label {
            text: replaceText(menuBarItem.text)
            font: menuBarItem.font
        }
        onDoubleClicked: clicked()
    }

    function reload() {
        /*if(nativeMenuBarEnabled)
        {
            root.visible = false;
            return;
        }*/

        var oldObjects = [];

        for (var i = 0; i < priv.menuObjects.length; i++)
            oldObjects.push(priv.menuObjects[i]);

        priv.menuObjects.length = 0;
        createMenuBar(root, "CustomMenu", "CustomMenuItem", "CustomMenuSeparator");

        for (i = 0; i < oldObjects.length; i++)
            removeMenu(oldObjects[i]);
    }

    /*Connections {
        target: // TODO: Add a class for the menu bar reload signal
        function onMenuBarReloadTriggered() {
            for(var i = 0; i < root.count; i++)
                root.menuAt(i).close();
            root.reload();
        }
    }*/

    Component.onCompleted: reload();

    /*onEnabledChanged: {
        if(platformMenuBarLoader.active)
            platformMenuBarLoader.item.reload();
    }

    Loader {
        id: platformMenuBarLoader
        active: // whether the native menu bar is active

        sourceComponent: Platform.MenuBar {
            id: platformMenuBar
            function reload() {
                clear();
                if(root.enabled)
                    createMenuBar(platformMenuBar, "Platform.Menu", "Platform.MenuItem", "Platform.MenuSeparator");
            }

            Connections {
                target: QmlUtils
                function onMenuBarReloadTriggered() {
                    platformMenuBar.reload();
                }
            }

            Component.onCompleted: reload();
        }
    }*/
}
