import QtQuick 2.0
import com.studio.Theme 1.0

Rectangle {
    id: cardBase
    property alias enabled: cardBaseMouse.enabled
    property alias pressed: cardBaseMouse.pressed
    signal clicked()

    height: 100
    width: 400
    radius: 8
    color: colors.get(colors.appTheme.foreground)
    opacity: pressed ? .7 : 1

    MouseArea {
        id: cardBaseMouse
        anchors.fill: parent
        onClicked: cardBase.clicked()
    }
}
