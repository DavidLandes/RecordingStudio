import QtQuick 2.0
import com.studio.Theme 1.0
import "common"
import "text"

CardBase {
    id: cardBaseItem
    property string name: ""
    property bool isSelected: false

    color: isSelected ? colors.get(Palette.Seafoam) : colors.get(Palette.Grey_20)
    Column {
        anchors {
            fill: parent
            margins: 10
        }
        MediumText {
            text: name
            width: parent.width
            height: implicitHeight
        }
    }
}
