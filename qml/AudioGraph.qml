import QtQuick 2.0
import com.studio.Theme 1.0
import com.studio.Audio 1.0
import "common"

Rectangle {
    property Track track
    radius: 8
    color: colors.get(Palette.Grey_17)
    Progress {
        id: audioProgress
        total: track ? track.source.duration * 1000 : 0
        value: track ? track.elapsed : 0
        width: parent.width
        height: 4
        radius: height/2
        anchors.top: parent.top
    }
}
