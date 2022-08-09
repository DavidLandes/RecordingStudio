import QtQuick 2.0
import com.studio.Theme 1.0

Item {
    id: progressBase
    property double percentage: progressBase.value / progressBase.total
    property var total: 1
    property var value: .5
    property int radius: 0
    property string background: colors.get(Palette.Grey_20)
    property string foreground: colors.get(Palette.Mahogany)
    Rectangle {
        id: back
        height: parent.height
        width: parent.width
        color: progressBase.background
        radius: progressBase.radius
    }
    Rectangle {
        id: front
        height: parent.height
        width: back.width * progressBase.percentage
        z: parent.z + 1
        color: progressBase.foreground
        radius: progressBase.radius
        anchors {
            left: back.left
            verticalCenter: back.verticalCenter
        }
    }
}
