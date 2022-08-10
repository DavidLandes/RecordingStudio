import QtQuick 2.0
import com.studio.Theme 1.0
import "../text"

Item {
    property int iconSize: 30
    property string iconColor: colors.get(Palette.White)
    property string iconCode: "plus"
    readonly property var icons: {
        "plus": "+",
        "refresh": "⟲",
        "play": "⏵︎",
        "caret-down": "▼",
        "pause": "⏸︎",
        "stop": "⯀",
        "record": "●",
        "kabob": "⋮",
    }
    CustomText {
        text: icons[iconCode]
        height: implicitHeight
        width: implicitWidth
        color: iconColor
        font.pixelSize: iconSize
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.centerIn: parent
    }
}
