import QtQuick 2.0
import "../text"
import "../buttons"

Item {
    anchors.fill: parent
    Column {
        id: leftCol
        width: parent.width / 2
        height: parent.height
        spacing: 4
        MediumText {
            text: "Audio Input"
            height: 50
            width: parent.width
            verticalAlignment: Text.AlignVCenter
        }
        MediumText {
            text: "Delayed Start"
            height: 50
            width: parent.width
            verticalAlignment: Text.AlignVCenter
        }
    }
    Column {
        id: rightCol
        width: parent.width / 2
        height: parent.height
        spacing: 4
        anchors.left: leftCol.right
        DropdownSelect {
            height: 50
            width: parent.width
            options: audio.recorder.devices
            selectedOption: audio.recorder.selectedDevice
            onSelectedOptionChanged: audio.recorder.selectedDevice = selectedOption;
        }
        DropdownSelect {
            height: 50
            width: parent.width / 3
            suffix: "sec"
            options: audio.startDelayOptions
            selectedOption: audio.startDelay
            onSelectedOptionChanged: audio.startDelay = selectedOption;
        }
    }
}
