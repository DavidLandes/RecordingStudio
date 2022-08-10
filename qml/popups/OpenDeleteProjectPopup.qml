import QtQuick 2.0
import QtQuick.Layouts 1.0
import com.studio.Theme 1.0
import "../text"
import "../buttons"
import "../common"

BasePopup {
    height: 350
    width: 350
    contentItem: Item {
        anchors.fill: parent
        SelectionList {
            id: selector
            property var projectNames: projects.getProjectNames()
            color: colors.get(Palette.Grey_22)
            width: parent.width * .9
            anchors {
                top: parent.top
                bottom: btnRow.top
                horizontalCenter: parent.horizontalCenter
                margins: 20
            }
            options: projectNames
        }
        RowLayout {
            id: btnRow
            width: parent.width * .7
            anchors {
                bottom: parent.bottom
                bottomMargin: 20
                horizontalCenter: parent.horizontalCenter
            }
            FlatButton {
                id: deleteBtn
                text: "Delete"
                enabled: !!selector.selectedOption
                color: colors.get(Palette.Grey_30)
                Layout.alignment: Qt.AlignHCenter
                onClicked: {
                    if (selector.selectedOption) {
                        projects.erase(selector.selectedOption);
                        selector.selectedOption = "";
                        selector.projectNames = projects.getProjectNames();
                    }
                }
            }
            FlatButton {
                id: openBtn
                text: "Open"
                enabled: !!selector.selectedOption
                color: colors.get(Palette.Seafoam)
                Layout.alignment: Qt.AlignHCenter
                onClicked: {
                    projects.open(selector.selectedOption);
                    close();
                }
            }
        }
    }
}
