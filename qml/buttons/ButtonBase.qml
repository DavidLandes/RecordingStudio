import QtQuick 2.0
import com.studio.Theme 1.0

Rectangle {
    id: baseBtn
    property Theme colorTheme: colors.appTheme
    property bool splashEnabled: false
    property bool enabled: true
    property bool pressed: false
    signal clicked()
    signal released()

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
        opacity: baseBtn.pressed ? .3 : 0
        anchors.fill: parent
        radius: parent.radius
        color: colors.get(colorTheme.foreground)
        Behavior on opacity {
            NumberAnimation {
                duration: !pressed ? 50 : 400
            }
        }
    }
}
