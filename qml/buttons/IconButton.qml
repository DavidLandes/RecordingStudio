import QtQuick 2.0
import com.studio.Theme 1.0
import "../text"
import "../common"

BaseButton {
    id: iconBtn
    property alias background: backgroundItem.data
    property string iconColor: colors.get(Palette.White)
    property string iconCode: "plus"
    height: 48
    width: 48
    splashEnabled: true
    color: "transparent"
    radius: height > width ? width / 2 : height / 2
    Icon {
        iconCode: iconBtn.iconCode
        iconColor: iconBtn.iconColor
        anchors.centerIn: parent
    }
    Item {
        id: backgroundItem
        anchors.fill: parent
        z: parent.z - 1
    }
}
