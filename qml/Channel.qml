import QtQuick 2.0
import com.studio.Theme 1.0
import com.studio.Track 1.0
import "buttons"
import "common"

CardBase {
    id: channelBase
    property Track track
    readonly property bool isPlayingAudio: track ? track.isPlaying : false
    readonly property var duration: track ? track.duration : 0
    readonly property var elapsed: track ? track.elapsed : 0
    signal deleteClicked()

    width: parent.width
    height: 200
    enabled: false
    color: colors.get(Palette.Grey_15)

    Item {
        id: btnColumn
        width: 64
        height: parent.height
        Column {
            spacing: 8
            anchors {
                fill: parent
                margins: 10
            }
            ShadedIconButton {
                iconCode: "kabob"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: channelBase.deleteClicked();
            }
            ShadedIconButton {
                property bool isSelected: false
                iconColor: colors.get(Palette.Red_80)
                iconCode: !isSelected ? "record" : "stop"
                enabled: !isPlayingAudio
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    isSelected = !isSelected;
                    if (isSelected) {
                        audio.recorder.start(track.filePath);
                    }
                    else {
                        audio.recorder.stop();
                    }
                }
            }
            ShadedIconButton {
                iconColor: colors.get(Palette.Green_70)
                iconCode: !isPlayingAudio ? "play" : "stop"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    if (!isPlayingAudio) {
                        track.play();
                    }
                    else {
                        track.stop();
                    }
                }
            }
        }
    }

    Item {
        height: parent.height
        anchors {
            left: btnColumn.right
            right: parent.right
            rightMargin: channelBase.radius
        }
        AudioGraph {
            id: graph
            track: channelBase.track
            height: parent.height * .9
            anchors {
                left: parent.left
                right: parent.right
                verticalCenter: parent.verticalCenter
            }
        }
    }
}
