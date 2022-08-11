import QtQuick 2.0
import com.studio.Theme 1.0
import "../buttons"

Rectangle {
    id: tabMenu
    property var menus: []
    property int selectedIndex: 0
    property string dividorColor: colors.get(Palette.Grey_30)
    property string selectedButtonColor: colors.get(Palette.Seafoam)
    property string buttonColor: colors.get(Palette.Grey_30)
    color: colors.get(Palette.Grey_22)
    width: 500
    height: 400
    radius: 8
    Item {
        id: menuItem
        width: 150
        anchors {
            top: parent.top
            left: parent.left
            bottom: parent.bottom
            margins: 10
        }
        Column {
            spacing: 10
            width: parent.width
            anchors.centerIn: parent
            Repeater {
                model: menus
                FlatButton {
                    text: modelData.title
                    width: parent.width * .9
                    color: index == tabMenu.selectedIndex ? tabMenu.selectedButtonColor : tabMenu.buttonColor
                    onClicked: tabMenu.selectedIndex = index;
                }
            }
        }
    }
    Rectangle {
        id: separator
        width: 2
        height: parent.height * .8
        color: tabMenu.dividorColor
        radius: width / 2
        anchors {
            left: menuItem.right
            verticalCenter: parent.verticalCenter
        }
    }
    Item {
        id: content
        anchors {
            top: parent.top
            left: separator.right
            right: parent.right
            bottom: parent.bottom
            margins: 48
        }
        Loader {
            anchors.fill: parent
            sourceComponent: tabMenu.menus[tabMenu.selectedIndex].component
        }
    }
}
