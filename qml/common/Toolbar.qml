import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import com.studio.Theme 1.0
import com.studio.Audio 1.0
import "../buttons"
import "../text"

Item {
    id: toolbarBase
    property string backgroundColor: colors.get(Palette.Grey_30)
    property string selectedItemColor: colors.get(Palette.Grey_25)
    property string selectedSubmenuItemColor: colors.get(Palette.Grey_20)
    property string textColor: colors.get(Palette.Grey_90)
    property string selectedTextColor: colors.get(Palette.Grey_80)
    property alias toolbarMenus: menuBar.menus
    width: parent.width
    height: 40
    MenuBar {
        id: menuBar
        anchors.fill: parent
        delegate: MenuBarItem {
            id: menuBarItem
            width: implicitWidth + 10
            height: parent.height
            contentItem: MediumText {
                text: menuBarItem.text
                opacity: enabled ? 1.0 : 0.3
                color: menuBarItem.highlighted ? toolbarBase.selectedTextColor : toolbarBase.textColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
            }
            background: Rectangle {
                anchors.fill: parent
                opacity: enabled ? 1 : 0.3
                color: menuBarItem.highlighted ? toolbarBase.selectedItemColor : "transparent"
            }
        }
        background: Rectangle {
            color: toolbarBase.backgroundColor
        }
    }
}
