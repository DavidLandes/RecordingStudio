import QtQuick 2.0
import com.studio.Theme 1.0
import "../text"
import "../buttons"
import "../common"

BasePopup {
    Component.onCompleted: open();
    height: 200
    width: 350
    contentItem: Item {
        anchors.fill: parent
        Item {
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                bottom: button.top
            }
            Input {
                id: input
                anchors.centerIn: parent
            }
        }
        FlatButton {
            id: button
            text: "Create"
            color: colors.get(Palette.Mahogany)
            enabled: input.text.trim() != ""
            anchors {
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
                bottomMargin: 20
            }
            onClicked: {
                projects.create(input.text.trim());
                close();
            }
        }
    }
}
