import QtQuick 2.0
import com.studio.Theme 1.0

IconButton {
    property string shadeColor: colors.get(Palette.Grey_20)
    background: Rectangle {
        anchors.fill: parent
        color: shadeColor
        radius: height / 2
    }
}
