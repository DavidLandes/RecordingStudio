import QtQuick 2.0
import com.studio.Theme 1.0
import "buttons"
import "text"

Rectangle {
    property string title: "Title"
    width: parent.width
    height: 80
    anchors.top: parent.top
    color: colors.get(Palette.Seafoam)
    LargerText {
        text: title
        anchors {
            leftMargin: 20
            left: parent.left
            verticalCenter: parent.verticalCenter
        }
    }
}
