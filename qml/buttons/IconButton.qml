import QtQuick 2.0
import com.studio.Theme 1.0
import "../text"

BaseButton {
    id: iconBtn
    property alias background: backgroundItem.data
    property string iconColor: colors.get(Palette.White)
    property string iconCode: "plus"
    readonly property var icons: {
        "plus": "+",
        "refresh": "⟲",
        "play": "⏵︎",
        "pause": "⏸︎",
        "stop": "⯀",
        "record": "●",
        "kabob": "⋮",
    }
    height: 48
    width: 48
    splashEnabled: true
    color: "transparent"
    radius: height > width ? width / 2 : height / 2

    LargeText {
        text: icons[iconCode]
        height: implicitHeight
        width: implicitWidth
        color: iconColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.centerIn: parent
    }
    Item {
        id: backgroundItem
        anchors.fill: parent
        z: parent.z - 1
    }
}
