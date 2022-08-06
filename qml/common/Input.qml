import QtQuick 2.0
import QtQuick.Controls 2.0
import com.studio.Theme 1.0
import "../text"
import "../buttons"

Rectangle {
    property string accentColor: colors.get(Palette.Mahogany)
    property string underlineColor: colors.get(Palette.Grey_40)
    property bool hasFocus: true
    readonly property string text: edit.text
    height: 48
    width: 256
    color: colors.get(Palette.Grey_25)

    TextEdit {
        id: edit
        anchors {
            fill: parent
            margins: 10
        }
        selectedTextColor: colors.get(Palette.Grey_90)
        color: colors.get(Palette.Grey_80)
        verticalAlignment: Text.AlignVCenter
        font {
            pixelSize: 18
        }
    }
    Rectangle {
        color: hasFocus ? accentColor : underlineColor
        height: 2
        width: parent.width
        anchors.bottom: parent.bottom
    }
}
