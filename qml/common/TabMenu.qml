import QtQuick 2.0
import com.studio.Theme 1.0
import "../buttons"

Rectangle {
    id: tabMenu
    property var menuTitles: []
    property list<Component> menuComponents
    property int selectedIndex: 0
    property string dividorColor: colors.get(Palette.Grey_30)
    color: colors.get(Palette.Grey_22)
    width: 500
    height: 400
    radius: 8
    Item {
        id: menus
        width: 150
        anchors {
            top: parent.top
            left: parent.left
            bottom: parent.bottom
            margins: 10
        }
        Column {
            spacing: 10
            anchors.centerIn: parent
            Repeater {
                model: menuTitles
                FlatButton {
                    text: modelData
                    onClicked: selectedIndex = index;
                }
            }
        }
    }
    Rectangle {
        id: separator
        width: 2
        height: parent.height * .8
        color: dividorColor
        radius: width / 2
        anchors {
            left: menus.right
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
            margins: 20
        }
        Loader {
            anchors.fill: parent
            sourceComponent: menuComponents[selectedIndex]
        }
    }
}
