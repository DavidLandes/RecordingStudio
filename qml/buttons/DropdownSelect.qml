import QtQuick 2.0
import com.studio.Theme 1.0
import "../text"
import "../common"

BaseButton {
    id: dropBase
    property var options: []
    property var selectedOption: options.length > 0 ? options[0] : undefined
    property string suffix: ""
    property alias isOpen: selector.isOpen
    height: 40
    width: 88
    radius: 8
    splashEnabled: true
    color: colors.get(Palette.Grey_25)
    MediumText {
        text: (dropBase.selectedOption ?? "") + (dropBase.selectedOption !== undefined ? " " : "") + dropBase.suffix
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideRight
        anchors {
            horizontalCenter: parent.horizontalCenter
            horizontalCenterOffset: -1 * dropIcon.iconSize / 2
            verticalCenter: parent.verticalCenter
        }
    }
    Icon {
        id: dropIcon
        iconCode: "caret-down"
        iconSize: 18
        anchors {
            right: parent.right
            rightMargin: 20
            verticalCenter: parent.verticalCenter
        }
    }
    SelectionList {
        id: selector
        property int drawerHeight: (dropBase.options.length * selector.itemHeight) + 20
        property int maxHeight: (selector.itemHeight * 5) + 20
        property bool isOpen: false
        options: dropBase.options
        visible: selector.isOpen
        height: drawerHeight <= selector.itemHeight * 5 ? drawerHeight : maxHeight
        width: parent.width
        y: dropBase.height + 4
        z: 100
        anchors.horizontalCenter: parent.horizontalCenter
        onSelectedOptionChanged: {
            dropBase.selectedOption = selector.selectedOption;
            selector.isOpen = false;
        }
    }
    onClicked: selector.isOpen = !selector.isOpen;
}
