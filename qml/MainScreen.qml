import QtQuick 2.0
import QtQuick.Layouts 1.0
import com.studio.Theme 1.0
import "common"
import "buttons"
import "popups"

Item {
    Header {
        id: header
        title: "Recording Studio"
    }
    ProjectToolbar {
        id: tools
        anchors.top: header.bottom
    }
    MicrophoneList {
        id: mics
        width: 300
        anchors {
            left: parent.left
            top: tools.bottom
            bottom: parent.bottom
        }
    }
    Item {
        id: editorPane
        anchors {
            top: tools.bottom
            left: mics.right
            right: parent.right
            bottom: parent.bottom
        }
        TrackList {
            anchors.fill: parent
        }
    }
}
