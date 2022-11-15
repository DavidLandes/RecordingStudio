import QtQuick 2.0
import com.studio.Theme 1.0
import "../text"
import "../buttons"

Rectangle {
    id: listBase
    property var options: []
    property var selectedOption
    property string selectedColor: colors.get(Palette.Grey_30)
    property string hoverColor: colors.get(Palette.Grey_25)
    property int itemHeight: 50
    property bool forceSelection: true
    color: colors.get(Palette.Grey_18)
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
            height: listBase.itemHeight
            width: parent.width
            color: (listItemMouse.containsMouse ? listBase.hoverColor : (selectedOption === modelData ? listBase.selectedColor : "transparent"))
            MediumText {
                text: modelData ? modelData : ""
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            MouseArea {
                id: listItemMouse
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    if (!forceSelection && selectedOption === modelData) {
                        selectedOption = null;
                    }
                    else {
                        selectedOption = modelData;
                    }
                }
            }
        }
    }
}
