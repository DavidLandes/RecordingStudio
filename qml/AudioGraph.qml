import QtQuick 2.0
import com.studio.Theme 1.0
import com.studio.Track 1.0
import "common"

Rectangle {
    property Track track
    radius: 8
    color: colors.get(Palette.Grey_17)
    Progress {
        total: track ? track.duration : 0
        value: track ? track.elapsed : 0
        width: parent.width
        height: 4
        radius: height/2
        anchors.top: parent.top
    }
}
