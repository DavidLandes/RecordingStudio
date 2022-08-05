import QtQuick 2.0
import QtQuick.Layouts 1.0
import com.studio.Theme 1.0
import "buttons"

Rectangle {
    color: colors.get(Palette.Grey_10)
    ListView {
        model: projects.current.tracks
        spacing: 10
        clip: true
        anchors {
            fill: parent
            margins: 20
        }
        delegate: Channel {
            track: modelData
            width: parent.width * .95
            anchors.horizontalCenter: parent.horizontalCenter
            onDeleteClicked: projects.current.deleteTrack(index);
        }
    }
}
