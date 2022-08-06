import QtQuick 2.0
import com.studio.Theme 1.0
import "../text"
import "../buttons"

Rectangle {
    id: listBase
    property var options: []
    property var selectedOption
    property string selectedColor: colors.get(Palette.Grey_25)
    color: colors.get(Palette.Grey_15)
    width: 200
    height: 400
    radius: 8
    ListView {
        anchors {
            fill: parent
            margins: 10
        }
        model: options
        clip: true
        delegate: Rectangle {
            radius: listBase.radius
            height: 50
            width: parent.width
            color: selectedOption == modelData ? selectedColor : "transparent"
            MediumText {
                text: modelData
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            MouseArea {
                anchors.fill: parent
                onClicked: selectedOption = modelData;
            }
        }
    }
}
