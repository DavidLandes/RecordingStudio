import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import com.studio.Theme 1.0
import com.studio.Audio 1.0
import "../buttons"
import "../text"

Menu {
    id: menuTab
    property string selectedItemColor: colors.get(Palette.Grey_22)
    property string selectedSubmenuItemColor: colors.get(Palette.Grey_20)
    property string textColor: colors.get(Palette.Grey_80)
    property string selectedTextColor: colors.get(Palette.Grey_90)
    property int radius: 8
    property int itemHeight: 50
    property var menuItems: []
    signal submenuClicked(var submenu)
    title: "Title"
    width: 256
    height: (menuTab.itemHeight * submenuList.count)
    Repeater {
        id: submenuList
        model: menuTab.menuItems
        MenuItem {
            id: menuItem
            text: modelData.title
            height: menuTab.itemHeight
            anchors {
                left: parent.left
                right: parent.right
                topMargin: 4
                bottomMargin: 4
            }
            contentItem: SmallText {
                text: menuItem.text
                opacity: enabled ? 1.0 : 0.3
                color: menuItem.highlighted ? menuTab.selectedTextColor : menuTab.textColor
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
                anchors.leftMargin: 16
            }
            background: Rectangle {
                anchors.fill: parent
                opacity: enabled ? 1 : 0.3
                color: menuItem.highlighted ? menuTab.selectedSubmenuItemColor : menuTab.selectedItemColor
            }
            onTriggered: menuTab.submenuClicked(modelData.title)
        }
    }
    background: Rectangle {
        radius: menuTab.radius
        color: menuTab.selectedItemColor
        width: menuTab.width
        height: (menuTab.itemHeight * submenuList.count) + menuTab.radius
    }
}
