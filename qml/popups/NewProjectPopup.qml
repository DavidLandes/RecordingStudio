import QtQuick 2.0
import com.studio.Theme 1.0
import "../text"
import "../buttons"

BasePopup {
    Component.onCompleted: open();
    height: 200
    width: 350
    contentItem: Item {
        anchors.fill: parent
        FlatButton {
            text: "Create"
            color: colors.get(Palette.Mahogany)
            anchors {
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
                bottomMargin: 20
            }
            onClicked: {
                projects.create(new Date().getTime() + "_project")
                close();
            }
        }
    }
}
