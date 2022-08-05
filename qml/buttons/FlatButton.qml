import QtQuick 2.0
import "../text"

BaseButton {
    id: flatBtnBase
    property string text: ""
    height: 48
    width: 96
    radius: 8
    splashEnabled: true
    MediumText {
        text: flatBtnBase.text
        height: implicitHeight
        width: implicitWidth
        anchors.centerIn: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
