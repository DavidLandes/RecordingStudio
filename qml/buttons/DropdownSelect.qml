import QtQuick 2.0
import QtQuick.Controls 2.15
import com.studio.Theme 1.0
import "../text"
import "../common"

BaseButton {
    id: dropBase
    property var options: []
    property var selectedOption: options.length > 0 ? options[0] : undefined
    property string suffix: ""
    property alias forceSelection: selectorList.forceSelection
    height: 40
    width: 88
    radius: 8
    splashEnabled: true
    color: colors.get(Palette.Grey_25)
    onClicked: selector.visible = !selector.visible;
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
    Popup {
        id: selector
        property int drawerHeight: (dropBase.options.length * selectorList.itemHeight) + 20
        property int maxHeight: (selectorList.itemHeight * 5) + 20
        modal: true
        dim: false
        visible: false
        y: dropBase.height + 4
        background: SelectionList {
            id: selectorList
            onHeightChanged: console.log(selector.drawerHeight)
            height: selector.drawerHeight <= selectorList.itemHeight * 5 ? selector.drawerHeight : selector.maxHeight
            width: dropBase.width
            options: dropBase.options
            onSelectedOptionChanged: {
                dropBase.selectedOption = selectedOption;
                selector.visible = false;
            }
        }
    }
}
