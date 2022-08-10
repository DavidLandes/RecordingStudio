import QtQuick 2.0
import com.studio.Theme 1.0
import "buttons"

Rectangle {
    color: colors.get(Palette.Grey_11)
    ListView {
        model: projects.current.tracks
        spacing: 10
        clip: true
        anchors {
            fill: parent
            leftMargin: 20
            rightMargin: 20
        }
        header: Item { height: 20; width: parent.width; }
        footer: Item { height: 20; width: parent.width; }
        delegate: Channel {
            track: modelData
            width: parent.width * .95
            anchors.horizontalCenter: parent.horizontalCenter
            onDeleteClicked: projects.current.deleteTrack(index);
        }
    }
}
