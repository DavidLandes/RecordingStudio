import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import "common"

Window {
    id: mainWindow
    visible: true
    width: 1280
    height: 960
    title: " "
    MainScreen {
        anchors.fill: parent
        focus: true
        Keys.onPressed: application.onKeyboardEvent(event.text);
    }
}
