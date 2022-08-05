import QtQuick 2.0
import QtQuick.Controls 2.0
import com.studio.Theme 1.0

Popup {
    id: basePopupItem
    property string backgroundColor: colors.get(Palette.Grey_20)
    property int radius: 16
    height: 200
    width: 350
    anchors.centerIn: parent
    dim: true
    modal: true
    background: Rectangle {
        radius: basePopupItem.radius
        color: basePopupItem.backgroundColor
        anchors.fill: parent
    }
}
