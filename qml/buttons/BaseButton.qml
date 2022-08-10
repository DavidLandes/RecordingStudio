import QtQuick 2.0
import com.studio.Theme 1.0

Rectangle {
    id: baseBtn
    property string splashColor: colors.get(Palette.Grey_40)
    property bool splashEnabled: false
    property bool enabled: true
    property bool pressed: false
    signal clicked()
    signal released()
    opacity: enabled ? 1 : .6
    color: "transparent"
    MouseArea {
        id: mouseBase
        anchors.fill: parent
        enabled: baseBtn.enabled
        onPressedChanged: baseBtn.pressed = pressed;
        onClicked: baseBtn.clicked();
        onReleased: baseBtn.released();
    }
    Rectangle {
        id: splash
        visible: baseBtn.splashEnabled
        opacity: baseBtn.pressed ? .5 : 0
        anchors.fill: parent
        radius: parent.radius
        color: baseBtn.splashColor
        Behavior on opacity {
            NumberAnimation {
                duration: !pressed ? 50 : 400
            }
        }
    }
}
