import QtQuick 2.0
import QtQuick.Layouts 1.0
import com.studio.Theme 1.0
import "buttons"

Rectangle {
    height: parent.height
    width: 500
    color: colors.get(Palette.Grey_15)
    ListView {
        model: audio.recorder.devices
        clip: true
        anchors.fill: parent
        spacing: 10
        header: Item { height: 10 }
        delegate: Device {
            name: modelData
            width: parent.width * .9
            isSelected: modelData == audio.recorder.selectedDevice
            anchors.centerIn: parent
            onClicked: audio.recorder.selectedDevice = (isSelected ? "" : modelData);
        }
    }
}

